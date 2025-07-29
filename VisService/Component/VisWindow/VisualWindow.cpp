#include "VisualWindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QEventLoop>
#include <QGridLayout>
#include <QFileDialog>
#include "Graphics/VGraphicsItem.h"
#include "Graphics/VGraphicsScene.h"
#include "Graphics/VGraphicsView.h"
#include "Graphics/VGraphicsDrawTool.h"

namespace VisWindow
{
	class VisualWindowPrivate
	{
	public:
		VisualWindowPrivate();
		~VisualWindowPrivate();
		void ReadImage(const QString& filename, uchar* pData, int* width, int* height, int* type, int* channel);
		void ReadImageDialog(uchar* pData, int* width, int* height, int* type, int* channel);
		void SetPen(const QPen& _pen);
		void SetBrush(const QBrush& _brush);
		void DispImage(const QImage& qimg);
		void DispRect(const QRect& rect);
		void DispCircle(double x, double y, double Radius);
		void DispEllipse(double x, double y, double Phi, double w, double h);
		void DispPolygon(const QPolygon& polygon);
		void DispPainterPath(const QPainterPath& path);
		void ClearDisp();
		VGraphicsRectItem* DrawRect();
		VGraphicsEllipseItem* DrawEllipse();
		VGraphicsPolygonItem* DrawPolygon();

	private:
		void SetImg(const QPixmap& pixMap);
		
	public:
		VGraphicsView* m_pVGraphicsView;

	private:
		QPen m_pen;
		QBrush m_brush;
		VGraphicsScene* m_pVGraphicsScene;
		QGraphicsPixmapItem* m_pPixmapItem;
		QSize m_imageSize;
		bool m_isFirstDispImg;
		std::vector<QGraphicsItem*> m_vDisplayedItem;
		QEventLoop* m_pEloop;
	};

	VisualWindowPrivate::VisualWindowPrivate()
	{
		m_pVGraphicsScene = new VGraphicsScene;
		m_pVGraphicsView = new VGraphicsView(m_pVGraphicsScene);
		m_pPixmapItem = nullptr;
		m_imageSize = QSize(0, 0);
		m_isFirstDispImg = true;
		m_pEloop = new QEventLoop;
	}

	VisualWindowPrivate::~VisualWindowPrivate()
	{
		delete m_pVGraphicsView;
	}

	void VisualWindowPrivate::ReadImage(const QString& filename, uchar* pData, int* width, int* height, int* type, int* channel)
	{
		QImage qimg(filename);
		auto img_fmt = qimg.format();
		if (img_fmt == QImage::Format_Indexed8 || img_fmt == QImage::Format_Grayscale8)
		{
			pData = (uchar*)qimg.bits();
			*width = qimg.width();
			*height = qimg.height();
			*type = 0;
			*channel = 1;
		}
		else if (img_fmt == QImage::Format_RGB888)
		{
			pData = (uchar*)qimg.bits();
			*width = qimg.width();
			*height = qimg.height();
			*type = 0;
			*channel = 3;
		}
		SetImg(QPixmap::fromImage(qimg));
	}

	void VisualWindowPrivate::ReadImageDialog(uchar* pData, int* width, int* height, int* type, int* channel)
	{
		QString fileName = QFileDialog::getOpenFileName(nullptr, "选择图片", "", "Images (*.png *.jpg *.bmp *.jpeg)");
		ReadImage(fileName, pData, width, height, type, channel);
	}

	void VisualWindowPrivate::SetPen(const QPen& _pen)
	{
		m_pen = _pen;
	}

	void VisualWindowPrivate::SetBrush(const QBrush& _brush)
	{
		m_brush = _brush;
	}

	void VisualWindowPrivate::DispImage(const QImage& qimg)
	{
		SetImg(QPixmap::fromImage(qimg));
	}

	void VisualWindowPrivate::DispRect(const QRect& rect)
	{
		auto* _item = m_pVGraphicsScene->addRect(rect, m_pen, m_brush);
		_item->setZValue(1);
		m_vDisplayedItem.push_back(_item);
	}

	void VisualWindowPrivate::DispCircle(double x, double y, double Radius)
	{
		auto* _item = m_pVGraphicsScene->addEllipse(x, y, Radius * 2, Radius * 2, m_pen, m_brush);
		_item->setZValue(1);
		m_vDisplayedItem.push_back(_item);
	}

	void VisualWindowPrivate::DispEllipse(double x, double y, double Phi, double w, double h)
	{
		auto* _item = m_pVGraphicsScene->addEllipse(x, y, w, h, m_pen, m_brush);
		_item->setZValue(1);
		m_vDisplayedItem.push_back(_item);
	}

	void VisualWindowPrivate::DispPolygon(const QPolygon& polygon)
	{
		auto* _item = m_pVGraphicsScene->addPolygon(polygon, m_pen, m_brush);
		_item->setZValue(1);
		m_vDisplayedItem.push_back(_item);
	}

	void VisualWindowPrivate::DispPainterPath(const QPainterPath& path)
	{
		auto* _item = m_pVGraphicsScene->addPath(path, m_pen, m_brush);
		_item->setZValue(1);
		m_vDisplayedItem.push_back(_item);
	}
	void VisualWindowPrivate::ClearDisp()
	{
		for (auto pItem : m_vDisplayedItem)
		{
			m_pVGraphicsScene->removeItem(pItem);
			delete pItem;
		}
		m_vDisplayedItem.clear();
	}

	VGraphicsRectItem* VisualWindowPrivate::DrawRect()
	{
		VGraphicsDrawTool::c_drawShape = DrawShape_Rectangle;
		VGraphicsDrawTool::c_pen = m_pen;
		VGraphicsDrawTool::c_brush = m_brush;
		QGraphicsItem* item = nullptr;
		QObject::disconnect(m_pVGraphicsScene, &VGraphicsScene::Signals_itemAdded, 0, 0);
		QObject::connect(m_pVGraphicsScene, &VGraphicsScene::Signals_itemAdded, [&](QGraphicsItem* _item)
		{
			item = _item;
			m_pEloop->quit();
		});
		m_pEloop->exec();
		if (item != nullptr)
		{
			return static_cast<VGraphicsRectItem*>(item);
		}
		else
		{
			return nullptr;
		}
	}

	VGraphicsEllipseItem* VisualWindowPrivate::DrawEllipse()
	{
		VGraphicsDrawTool::c_drawShape = DrawShape_Ellipse;
		VGraphicsDrawTool::c_pen = m_pen;
		VGraphicsDrawTool::c_brush = m_brush;
		QGraphicsItem* item = nullptr;
		QObject::disconnect(m_pVGraphicsScene, &VGraphicsScene::Signals_itemAdded, 0, 0);
		QObject::connect(m_pVGraphicsScene, &VGraphicsScene::Signals_itemAdded, [&](QGraphicsItem* _item)
		{
			item = _item;
			m_pEloop->quit();
		});
		m_pEloop->exec();
		if (item != nullptr)
		{
			return static_cast<VGraphicsEllipseItem*>(item);
		}
		else
		{
			return nullptr;
		}
	}

	VGraphicsPolygonItem* VisualWindowPrivate::DrawPolygon()
	{
		VGraphicsDrawTool::c_drawShape = DrawShape_Polygon;
		VGraphicsDrawTool::c_pen = m_pen;
		VGraphicsDrawTool::c_brush = m_brush;
		QGraphicsItem* item = nullptr;
		QObject::disconnect(m_pVGraphicsScene, &VGraphicsScene::Signals_itemAdded, 0, 0);
		QObject::connect(m_pVGraphicsScene, &VGraphicsScene::Signals_itemAdded, [&](QGraphicsItem* _item)
		{
			item = _item;
			m_pEloop->quit();
		});
		m_pEloop->exec();
		if (item != nullptr)
		{
			return static_cast<VGraphicsPolygonItem*>(item);
		}
		else
		{
			return nullptr;
		}
	}

	void VisualWindowPrivate::SetImg(const QPixmap& pixMap)
	{
		if (m_pPixmapItem)
		{
			m_pPixmapItem->setPixmap(pixMap);
		}
		else
		{
			m_pPixmapItem = m_pVGraphicsScene->addPixmap(pixMap);
		}
		if (m_pVGraphicsScene->sceneRect() != m_pPixmapItem->boundingRect())
		{
			m_pVGraphicsScene->setSceneRect(m_pPixmapItem->boundingRect());
		}
		m_pPixmapItem->setZValue(0);
		m_pPixmapItem->update();
		if (pixMap.size() != m_imageSize)
		{
			m_isFirstDispImg = true;
			m_imageSize = pixMap.size();
		}
		if (m_isFirstDispImg)
		{
			m_pVGraphicsView->fitInView(m_pVGraphicsView->sceneRect(), Qt::KeepAspectRatio);
			m_isFirstDispImg = false;
		}
	}


#pragma region VisualWindow
	VisualWindow::VisualWindow(QWidget* parent) : QWidget(parent), m_pVisualWindowPrivate(new VisualWindowPrivate)
	{
		QGridLayout* pLayout = new QGridLayout(this);
		pLayout->addWidget(m_pVisualWindowPrivate->m_pVGraphicsView);
		this->setLayout(pLayout);
	}

	VisualWindow::~VisualWindow()
	{
		delete m_pVisualWindowPrivate;
	}

	void VisualWindow::SetPen(const QPen& _pen)
	{
		m_pVisualWindowPrivate->SetPen(_pen);
	}

	void VisualWindow::SetBrush(const QBrush& _brush)
	{
		m_pVisualWindowPrivate->SetBrush(_brush);
	}

	void VisualWindow::DispImage(const QImage& _img)
	{
		m_pVisualWindowPrivate->DispImage(_img);
	}

	void VisualWindow::DispRect(const QRect& rect)
	{
		m_pVisualWindowPrivate->DispRect(rect);
	}

	void VisualWindow::DispCircle(double x, double y, double Radius)
	{
		m_pVisualWindowPrivate->DispCircle(x, y, Radius);
	}

	void VisualWindow::DispEllipse(double x, double y, double Phi, double w, double h)
	{
		m_pVisualWindowPrivate->DispEllipse(x, y, Phi, w, h);
	}

	void VisualWindow::DispPolygon(const QPolygon& polygon)
	{
		m_pVisualWindowPrivate->DispPolygon(polygon);
	}

	void VisualWindow::DispPainterPath(const QPainterPath& path)
	{
		m_pVisualWindowPrivate->DispPainterPath(path);
	}

	void VisualWindow::ClearDisp()
	{
		m_pVisualWindowPrivate->ClearDisp();
	}

	VGraphicsRectItem* VisualWindow::DrawRect()
	{
		return m_pVisualWindowPrivate->DrawRect();
	}

	VGraphicsEllipseItem* VisualWindow::DrawEllipse()
	{
		return m_pVisualWindowPrivate->DrawEllipse();
	}

	VGraphicsPolygonItem* VisualWindow::DrawPolygon()
	{
		return m_pVisualWindowPrivate->DrawPolygon();
	}

#pragma endregion
}
