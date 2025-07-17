#include "VGraphicsView.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QFileDialog>
#include "VGraphicsItem.h"
#include "VGraphicsScene.h"

namespace VisWindow
{
	VGraphicsView::VGraphicsView(QGraphicsScene* scene) : QGraphicsView(scene)
	{
		setViewport(new QWidget);
		setAttribute(Qt::WA_DeleteOnClose);
		m_untitled = true;
		m_modified = false;
	}

	void VGraphicsView::ZoomIn()
	{
		scale(1.2, 1.2);
	}

	void VGraphicsView::ZoomOut()
	{
		scale(1 / 1.2, 1 / 1.2);
	}

	void VGraphicsView::NewFile()
	{
		static int sequenceNumber = 1;
		m_untitled = true;
		curFile = tr("drawing%1.xml").arg(sequenceNumber++);
		setWindowTitle(curFile + "[*]");
	}

	bool VGraphicsView::LoadFile(const QString& fileName)
	{
		QFile file(fileName);
		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, tr("Qt Drawing"),
								 tr("Cannot read file %1:\n%2.")
								 .arg(fileName)
								 .arg(file.errorString()));
			return false;
		}

		QXmlStreamReader xml(&file);
		if (xml.readNextStartElement())
		{
			if (xml.name() == tr("canvas"))
			{
				int width = xml.attributes().value(tr("width")).toInt();
				int height = xml.attributes().value(tr("height")).toInt();
				scene()->setSceneRect(0, 0, width, height);
				LoadCanvas(&xml);
			}
		}

		SetCurrentFile(fileName);
		return !xml.error();
	}

	bool VGraphicsView::Save()
	{
		if (m_untitled)
		{
			return SaveAs();
		}
		else
		{
			return SaveFile(curFile);
		}
	}

	bool VGraphicsView::SaveAs()
	{
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
														curFile);
		if (fileName.isEmpty())
			return false;

		return SaveFile(fileName);
	}
	bool VGraphicsView::SaveFile(const QString& fileName)
	{
		QFile file(fileName);
		if (!file.open(QFile::WriteOnly | QFile::Text))
		{
			QMessageBox::warning(this, tr("Qt Drawing"),
								 tr("Cannot write file %1:\n%2.")
								 .arg(fileName)
								 .arg(file.errorString()));
			return false;
		}
		QXmlStreamWriter xml(&file);
		xml.setAutoFormatting(true);
		xml.writeStartDocument();
		xml.writeDTD("<!DOCTYPE qdraw>");
		xml.writeStartElement("canvas");
		xml.writeAttribute("width", QString("%1").arg(scene()->width()));
		xml.writeAttribute("height", QString("%1").arg(scene()->height()));
		foreach(QGraphicsItem * item, scene()->items())
		{
			VAbstractQGraphicsItem* pItem = qgraphicsitem_cast<VAbstractQGraphicsItem*>(item);
			QGraphicsItemGroup* g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
			if (pItem && !qgraphicsitem_cast<VGraphicsItemControlBlock*>(pItem) && !g)
			{
				pItem->SaveToXml(&xml);
			}
		}
		xml.writeEndElement();
		xml.writeEndDocument();
		SetCurrentFile(fileName);
		return true;
	}

	QString VGraphicsView::UserFriendlyCurrentFile()
	{
		return StrippedName(curFile);
	}

	QString VGraphicsView::CurrentFile()
	{
		return curFile;
	}

	void VGraphicsView::SetModified(bool value)
	{
		m_modified = value;
	}

	bool VGraphicsView::IsModified() const
	{
		return m_modified;
	}

	void VGraphicsView::closeEvent(QCloseEvent* event)
	{
		if (MaybeSave())
		{
			event->accept();
		}
		else
		{
			event->ignore();
		}
	}

	void VGraphicsView::mouseMoveEvent(QMouseEvent* event)
	{
		QPointF pt = mapToScene(event->pos());
		emit Signals_positionChanged(pt.x(), pt.y());
		QGraphicsView::mouseMoveEvent(event);
	}

	void VGraphicsView::resizeEvent(QResizeEvent* event)
	{
		QGraphicsView::resizeEvent(event);
	}

	void VGraphicsView::scrollContentsBy(int dx, int dy)
	{
		QGraphicsView::scrollContentsBy(dx, dy);
	}

	bool VGraphicsView::MaybeSave()
	{
		if (IsModified())
		{
			QMessageBox::StandardButton ret;
			ret = QMessageBox::warning(this, tr("MDI"), tr("'%1' has been modified.\n""Do you want to save your changes?").arg(UserFriendlyCurrentFile()), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
			if (ret == QMessageBox::Save)
			{
				return Save();
			}
			else if (ret == QMessageBox::Cancel)
			{
				return false;
			}
		}
		return true;
	}

	void VGraphicsView::SetCurrentFile(const QString& fileName)
	{
		curFile = QFileInfo(fileName).canonicalFilePath();
		m_untitled = false;
		SetModified(false);
		setWindowModified(false);
		setWindowTitle(UserFriendlyCurrentFile() + "[*]");
	}

	QString VGraphicsView::StrippedName(const QString& fullFileName)
	{
		return QFileInfo(fullFileName).fileName();
	}

	void VGraphicsView::LoadCanvas(QXmlStreamReader* xml)
	{
		Q_ASSERT(xml->isStartElement() && xml->name() == "canvas");

		while (xml->readNextStartElement())
		{
			VAbstractQGraphicsItem* item = NULL;
			if (xml->name() == tr("rect"))
			{
				item = new VGraphicsRectItem(QRect(0, 0, 1, 1));
			}
			else if (xml->name() == tr("roundrect"))
			{
				item = new VGraphicsRectItem(QRect(0, 0, 1, 1), true);
			}
			else if (xml->name() == tr("ellipse"))
				item = new VGraphicsEllipseItem(QRect(0, 0, 1, 1));
			else if (xml->name() == tr("polygon"))
				item = new VGraphicsPolygonItem();
			else if (xml->name() == tr("bezier"))
				item = new VGraphicsBezierItem();
			else if (xml->name() == tr("polyline"))
				item = new VGraphicsBezierItem(false);
			else if (xml->name() == tr("line"))
				item = new VGraphicsLineItem();
			else if (xml->name() == tr("group"))
				item = qgraphicsitem_cast<VAbstractQGraphicsItem*>(loadGroupFromXML(xml));
			else
				xml->skipCurrentElement();

			if (item && item->LoadFromXml(xml))
				scene()->addItem(item);
			else if (item)
				delete item;
		}
	}

	VGraphicsItemGroup* VGraphicsView::loadGroupFromXML(QXmlStreamReader* xml)
	{
		QList<QGraphicsItem*> items;
		qreal angle = xml->attributes().value(tr("rotate")).toDouble();
		while (xml->readNextStartElement())
		{
			VAbstractQGraphicsItem* item = NULL;
			if (xml->name() == tr("rect"))
			{
				item = new VGraphicsRectItem(QRect(0, 0, 1, 1));
			}
			else if (xml->name() == tr("roundrect"))
			{
				item = new VGraphicsRectItem(QRect(0, 0, 1, 1), true);
			}
			else if (xml->name() == tr("ellipse"))
				item = new VGraphicsEllipseItem(QRect(0, 0, 1, 1));
			else if (xml->name() == tr("polygon"))
				item = new VGraphicsPolygonItem();
			else if (xml->name() == tr("bezier"))
				item = new VGraphicsBezierItem();
			else if (xml->name() == tr("polyline"))
				item = new VGraphicsBezierItem(false);
			else if (xml->name() == tr("line"))
				item = new VGraphicsLineItem();
			else if (xml->name() == tr("group"))
				item = qgraphicsitem_cast<VAbstractQGraphicsItem*>(loadGroupFromXML(xml));
			else
				xml->skipCurrentElement();
			if (item && item->LoadFromXml(xml))
			{
				scene()->addItem(item);
				items.append(item);
			}
			else if (item)
				delete item;
		}
		if (items.count() > 0)
		{
			VGraphicsScene* s = dynamic_cast<VGraphicsScene*>(scene());
			VGraphicsItemGroup* group = s->CreateGroup(items, false);
			if (group)
			{
				group->setRotation(angle);
				group->UpdateCoordinate();
			}
			return group;
		}
		return 0;
	}
}
