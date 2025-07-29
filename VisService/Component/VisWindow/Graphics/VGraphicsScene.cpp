#include "VGraphicsScene.h"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <vector>
#include "VGraphicsItem.h"
#include "VGraphicsDrawTool.h"

namespace VisWindow
{
	VSceneGrid::VSceneGrid(const QSize& grid, const QSize& space) :m_sizeGrid(grid), m_sizeGridSpace(20, 20)
	{

	}

	void VSceneGrid::PaintGrid(QPainter* painter, const QRect& rect)
	{
		QColor c(Qt::darkCyan);
		QPen p(c);
		p.setStyle(Qt::DashLine);
		p.setWidthF(0.2);
		painter->setPen(p);
		painter->save();
		painter->setRenderHints(QPainter::Antialiasing, false);
		painter->fillRect(rect, Qt::white);
		for (int x = rect.left(); x < rect.right(); x += (int)(m_sizeGridSpace.width()))
		{
			painter->drawLine(x, rect.top(), x, rect.bottom());

		}
		for (int y = rect.top(); y < rect.bottom(); y += (int)(m_sizeGridSpace.height()))
		{
			painter->drawLine(rect.left(), y, rect.right(), y);
		}
		p.setStyle(Qt::SolidLine);
		p.setColor(Qt::black);
		painter->drawLine(rect.right(), rect.top(), rect.right(), rect.bottom());
		painter->drawLine(rect.left(), rect.bottom(), rect.right(), rect.bottom());
	}

	class BBoxSort
	{
	public:
		BBoxSort(QGraphicsItem* item, const QRectF& rect, VSceneAlignType alignType) : item_(item), box(rect), align(alignType)
		{
			//topLeft
			min_ = alignType == AlignType_Horzeven ? box.topLeft().x() : box.topLeft().y();
			//bottomRight
			max_ = alignType == AlignType_Horzeven ? box.bottomRight().x() : box.bottomRight().y();
			//width or height
			extent_ = alignType == AlignType_Horzeven ? box.width() : box.height();
			anchor = min_ * 0.5 + max_ * 0.5;
		}
		qreal min() {
			return min_;
		}
		qreal max() {
			return max_;
		}
		qreal extent() {
			return extent_;
		}
		QGraphicsItem* item_;
		qreal anchor;
		qreal min_;
		qreal max_;
		qreal extent_;
		QRectF box;
		VSceneAlignType align;
	};

	bool operator< (const BBoxSort& a, const BBoxSort& b)
	{
		return (a.anchor < b.anchor);
	}


	VGraphicsScene::VGraphicsScene(QObject* parent) : QGraphicsScene(parent), m_dx(0), m_dy(0), m_moved(false), m_pQGraphicsView(nullptr)
	{
		m_pVSceneGrid = new VSceneGrid();
	}

	VGraphicsScene::~VGraphicsScene()
	{
		if (m_pVSceneGrid)
		{
			delete m_pVSceneGrid;
		}
	}

	void VGraphicsScene::SetView(QGraphicsView* view)
	{
		m_pQGraphicsView = view;
	}

	QGraphicsView* VGraphicsScene::View()
	{
		return m_pQGraphicsView;
	}

	void VGraphicsScene::Align(VSceneAlignType alignType)
	{
		VAbstractQGraphicsItem* firstItem = qgraphicsitem_cast<VAbstractQGraphicsItem*>(selectedItems().first());
		if (!firstItem) return;
		QRectF rectref = firstItem->mapRectToScene(firstItem->boundingRect());
		int nLeft, nRight, nTop, nBottom;
		qreal width = firstItem->Width();
		qreal height = firstItem->Height();
		nLeft = nRight = rectref.center().x();
		nTop = nBottom = rectref.center().y();
		QPointF pt = rectref.center();
		if (alignType == AlignType_Horzeven || alignType == AlignType_Verteven)
		{
			std::vector<BBoxSort> sorted;
			foreach(QGraphicsItem * item, selectedItems()) {
				QGraphicsItemGroup* g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
				if (g)
					continue;
				sorted.push_back(BBoxSort(item, item->mapRectToScene(item->boundingRect()), alignType));
			}
			//sort bbox by anchors
			std::sort(sorted.begin(), sorted.end());
			size_t len = sorted.size();
			bool changed = false;
			//overall bboxes span
			float dist = (sorted.back().max() - sorted.front().min());
			//space eaten by bboxes
			float span = 0;
			for (unsigned int i = 0; i < len; i++)
			{
				span += sorted[i].extent();
			}
			//new distance between each bbox
			float step = (dist - span) / (len - 1);
			float pos = sorted.front().min();
			for (std::vector<BBoxSort>::iterator it(sorted.begin()); it < sorted.end(); ++it)
			{
				{
					QPointF t;
					if (alignType == AlignType_Horzeven)
						t.setX(pos - it->min());
					else
						t.setY(pos - it->min());
					it->item_->moveBy(t.x(), t.y());
					emit Signals_itemMoved(it->item_, t);
					changed = true;
				}
				pos += it->extent();
				pos += step;
			}
			return;
		}

		int i = 0;
		foreach(QGraphicsItem * item, selectedItems()) 
		{
			QGraphicsItemGroup* g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
			if (g)
				continue;
			QRectF rectItem = item->mapRectToScene(item->boundingRect());
			QPointF ptNew = rectItem.center();
			switch (alignType)
			{
			case VisWindow::AlignType_Up:
				ptNew.setY(nTop + (rectItem.height() - rectref.height()) / 2);
				break;
			case VisWindow::AlignType_Horz:
				ptNew.setY(pt.y());
				break;
			case VisWindow::AlignType_Vert:
				ptNew.setX(pt.x());
				break;
			case VisWindow::AlignType_Down:
				ptNew.setY(nBottom - (rectItem.height() - rectref.height()) / 2);
				break;
			case VisWindow::AlignType_Left:
				ptNew.setX(nLeft - (rectref.width() - rectItem.width()) / 2);
				break;
			case VisWindow::AlignType_Right:
				ptNew.setX(nRight + (rectref.width() - rectItem.width()) / 2);
				break;
			case VisWindow::AlignType_Center:
				ptNew = pt;
				break;
			case VisWindow::AlignType_Width:
			{
				VAbstractQGraphicsItem* aitem = qgraphicsitem_cast<VAbstractQGraphicsItem*>(item);
				if (aitem)
				{
					qreal fx = width / aitem->Width();
					if (fx == 1.0) break;
					aitem->Stretch(Right, fx, 1, aitem->Opposite(Right));
					aitem->UpdateCoordinate();
					emit Signals_itemResize(aitem, Right, QPointF(fx, 1));
				}
			}
			break;
			case VisWindow::AlignType_Height:
			{
				VAbstractQGraphicsItem* aitem = qgraphicsitem_cast<VAbstractQGraphicsItem*>(item);
				if (aitem)
				{

					qreal fy = height / aitem->Height();
					if (fy == 1.0) break;
					aitem->Stretch(Bottom, 1, fy, aitem->Opposite(Bottom));
					aitem->UpdateCoordinate();
					emit Signals_itemResize(aitem, Bottom, QPointF(1, fy));
				}
			}
			break;
			case VisWindow::AlignType_All:
			{
				VAbstractQGraphicsItem* aitem = qgraphicsitem_cast<VAbstractQGraphicsItem*>(item);
				if (aitem)
				{
					qreal fx = width / aitem->Width();
					qreal fy = height / aitem->Height();
					if (fx == 1.0 && fy == 1.0) break;
					aitem->Stretch(RightBottom, fx, fy, aitem->Opposite(RightBottom));
					aitem->UpdateCoordinate();
					emit Signals_itemResize(aitem, RightBottom, QPointF(fx, fy));
				}
			}
			break;
			default:
				break;
			}
			QPointF ptLast = rectItem.center();
			QPointF ptMove = ptNew - ptLast;
			if (!ptMove.isNull())
			{
				item->moveBy(ptMove.x(), ptMove.y());
				emit Signals_itemMoved(item, ptMove);
			}
			i++;
		}

	}

	void VGraphicsScene::MouseEvent(QGraphicsSceneMouseEvent* mouseEvent)
	{
		switch (mouseEvent->type())
		{
		case QEvent::GraphicsSceneMousePress:
			QGraphicsScene::mousePressEvent(mouseEvent);
			break;
		case QEvent::GraphicsSceneMouseMove:
			QGraphicsScene::mouseMoveEvent(mouseEvent);
			break;
		case QEvent::GraphicsSceneMouseRelease:
			QGraphicsScene::mouseReleaseEvent(mouseEvent);
			break;
		}
	}

	VGraphicsItemGroup* VGraphicsScene::CreateGroup(const QList<QGraphicsItem*>& items, bool isAdd)
	{
			// Build a list of the first item's ancestors
		QList<QGraphicsItem*> ancestors;
		int n = 0;
		QPointF pt = items.first()->pos();
		if (!items.isEmpty())
		{
			QGraphicsItem* parent = items.at(n++);
			while ((parent = parent->parentItem()))
				ancestors.append(parent);
		}
		// Find the common ancestor for all items
		QGraphicsItem* commonAncestor = 0;
		if (!ancestors.isEmpty())
		{
			while (n < items.size())
			{
				int commonIndex = -1;
				QGraphicsItem* parent = items.at(n++);
				do
				{
					int index = ancestors.indexOf(parent, qMax(0, commonIndex));
					if (index != -1)
					{
						commonIndex = index;
						break;
					}
				} while ((parent = parent->parentItem()));

				if (commonIndex == -1)
				{
					commonAncestor = 0;
					break;
				}

				commonAncestor = ancestors.at(commonIndex);
			}
		}

		// Create a new group at that level
		VGraphicsItemGroup* group = new VGraphicsItemGroup(commonAncestor);
		if (!commonAncestor && isAdd)
			addItem(group);
		foreach(QGraphicsItem * item, items) {
			item->setSelected(false);
			QGraphicsItemGroup* g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
			if (!g)
				group->addToGroup(item);
		}
		group->UpdateCoordinate();
		return group;
	}

	void VGraphicsScene::DestroyGroup(QGraphicsItemGroup* group)
	{
		group->setSelected(false);
		foreach(QGraphicsItem * item, group->childItems()) {
			item->setSelected(true);
			group->removeFromGroup(item);
		}
		removeItem(group);
		delete group;
	}

	void VGraphicsScene::drawBackground(QPainter* painter, const QRectF& rect)
	{
		QGraphicsScene::drawBackground(painter, rect);
		painter->fillRect(sceneRect(), Qt::white);
		if (m_pVSceneGrid)
		{
			m_pVSceneGrid->PaintGrid(painter, sceneRect().toRect());
		}
	}

	void VGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
	{

		VGraphicsDrawTool* tool = VGraphicsDrawTool::FindTool(VGraphicsDrawTool::c_drawShape);
		if (tool)
			tool->mousePressEvent(mouseEvent, this);
	}

	void VGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
	{
		VGraphicsDrawTool* tool = VGraphicsDrawTool::FindTool(VGraphicsDrawTool::c_drawShape);
		if (tool)
			tool->mouseMoveEvent(mouseEvent, this);
	}

	void VGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
	{
		VGraphicsDrawTool* tool = VGraphicsDrawTool::FindTool(VGraphicsDrawTool::c_drawShape);
		if (tool)
			tool->mouseReleaseEvent(mouseEvent, this);
	}

	void VGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvet)
	{
		VGraphicsDrawTool* tool = VGraphicsDrawTool::FindTool(VGraphicsDrawTool::c_drawShape);
		if (tool)
			tool->mouseDoubleClickEvent(mouseEvet, this);
	}

	void VGraphicsScene::keyPressEvent(QKeyEvent* e)
	{
		qreal dx = 0, dy = 0;
		m_moved = false;
		switch (e->key())
		{
		case Qt::Key_Up:
			dx = 0;
			dy = -1;
			m_moved = true;
			break;
		case Qt::Key_Down:
			dx = 0;
			dy = 1;
			m_moved = true;
			break;
		case Qt::Key_Left:
			dx = -1;
			dy = 0;
			m_moved = true;
			break;
		case Qt::Key_Right:
			dx = 1;
			dy = 0;
			m_moved = true;
			break;
		}
		m_dx += dx;
		m_dy += dy;
		if (m_moved)
			foreach(QGraphicsItem * item, selectedItems()) {
			item->moveBy(dx, dy);
		}
		QGraphicsScene::keyPressEvent(e);
	}

	void VGraphicsScene::keyReleaseEvent(QKeyEvent* e)
	{
		if (m_moved && selectedItems().count() > 0)
			emit Signals_itemMoved(NULL, QPointF(m_dx, m_dy));
		m_dx = m_dy = 0;
		QGraphicsScene::keyReleaseEvent(e);
	}
}