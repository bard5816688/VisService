#include "VGraphicsDrawTool.h"
#include "VGraphicsScene.h"
#include "VGraphicsItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

namespace VisWindow
{
	QList<VGraphicsDrawTool*> VGraphicsDrawTool::c_tools;
	QPointF VGraphicsDrawTool::c_down;
	QPointF VGraphicsDrawTool::c_last;
	quint32 VGraphicsDrawTool::c_nDownFlags;
	VGraphicsDrawShape VGraphicsDrawTool::c_drawShape = DrawShape_Selection; 
	QPen VGraphicsDrawTool::c_pen = Qt::NoPen;
	QBrush VGraphicsDrawTool::c_brush = Qt::NoBrush;

	static VGraphicsSelectTool  s_selectTool;
	static VGraphicsRectTool    s_rectTool(DrawShape_Rectangle);
	static VGraphicsRectTool    s_roundRectTool(DrawShape_Roundrect);
	static VGraphicsRectTool    s_ellipseTool(DrawShape_Ellipse);
	static VGraphicsPolygonTool s_lineTool(DrawShape_Line);
	static VGraphicsPolygonTool s_polygonTool(DrawShape_Polygon);
	static VGraphicsPolygonTool s_bezierTool(DrawShape_Bezier);
	static VGraphicsPolygonTool s_polylineTool(DrawShape_Polyline);

	enum eVGraphicsSelectToolMode
	{
		SelectToolMode_None,
		SelectToolMode_NetSelect,
		SelectToolMode_Move,
		SelectToolMode_Size,
		SelectToolMode_Rotate,
		SelectToolMode_Editor,
	};

	eVGraphicsSelectToolMode g_selectMode = SelectToolMode_None;
	int g_nDragHandle = Handle_None;

	static void setCursor(VGraphicsScene* scene, const QCursor& cursor)
	{
		QGraphicsView* view = scene->View();
		if (view)
			view->setCursor(cursor);
	}

	VGraphicsDrawTool::VGraphicsDrawTool(VGraphicsDrawShape shape)
	{
		m_drawShape = shape;
		m_hoverSizer = false;
		c_tools.push_back(this);
	}

	void VGraphicsDrawTool::mousePressEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		c_down = event->scenePos();
		c_last = event->scenePos();
	}

	void VGraphicsDrawTool::mouseMoveEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		c_last = event->scenePos();
	}

	void VGraphicsDrawTool::mouseReleaseEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		if (event->scenePos() == c_down)
			c_drawShape = DrawShape_Selection;
		setCursor(scene, Qt::ArrowCursor);
	}

	void VGraphicsDrawTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{

	}

	VGraphicsDrawTool* VGraphicsDrawTool::FindTool(VGraphicsDrawShape drawShape)
	{
		QList<VGraphicsDrawTool*>::const_iterator iter = c_tools.constBegin();
		for (; iter != c_tools.constEnd(); ++iter)
		{
			if ((*iter)->m_drawShape == drawShape)
				return (*iter);
		}
		return nullptr;
	}

	VGraphicsSelectTool::VGraphicsSelectTool() : VGraphicsDrawTool(DrawShape_Selection)
	{
		dashRect = 0;
		selLayer = 0;
		opposite_ = QPointF();
	}

	void VGraphicsSelectTool::mousePressEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		VGraphicsDrawTool::mousePressEvent(event, scene);
		if (event->button() != Qt::LeftButton) return;
		if (!m_hoverSizer)
			scene->MouseEvent(event);
		g_nDragHandle = Handle_None;
		g_selectMode = SelectToolMode_None;
		QList<QGraphicsItem*> items = scene->selectedItems();
		VAbstractQGraphicsItem* item = 0;
		if (items.count() == 1)
			item = qgraphicsitem_cast<VAbstractQGraphicsItem*>(items.first());
		if (item != 0)
		{

			g_nDragHandle = item->CollidesWithHandle(event->scenePos());
			if (g_nDragHandle != Handle_None && g_nDragHandle <= Left)
				g_selectMode = SelectToolMode_Size;
			else if (g_nDragHandle > Left)
				g_selectMode = SelectToolMode_Editor;
			else
				g_selectMode = SelectToolMode_Move;

			if (g_nDragHandle != Handle_None && g_nDragHandle <= Left)
			{
				opposite_ = item->Opposite(g_nDragHandle);
				if (opposite_.x() == 0)
					opposite_.setX(1);
				if (opposite_.y() == 0)
					opposite_.setY(1);
			}
			setCursor(scene, Qt::ClosedHandCursor);
		}
		else if (items.count() > 1)
			g_selectMode = SelectToolMode_Move;
		if (g_selectMode == SelectToolMode_None)
		{
			g_selectMode = SelectToolMode_NetSelect;
			if (scene->View())
			{
				QGraphicsView* view = scene->View();
				view->setDragMode(QGraphicsView::RubberBandDrag);
			}
		}
		if (g_selectMode == SelectToolMode_Move && items.count() == 1)
		{
			if (dashRect)
			{
				scene->removeItem(dashRect);
				delete dashRect;
				dashRect = 0;
			}
			dashRect = new QGraphicsPathItem(item->shape());
			dashRect->setPen(Qt::DashLine);
			dashRect->setPos(item->pos());
			dashRect->setTransformOriginPoint(item->transformOriginPoint());
			dashRect->setTransform(item->transform());
			dashRect->setRotation(item->rotation());
			dashRect->setScale(item->scale());
			dashRect->setZValue(item->zValue());
			scene->addItem(dashRect);
			initialPositions = item->pos();
		}
	}

	void VGraphicsSelectTool::mouseMoveEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		VGraphicsDrawTool::mouseMoveEvent(event, scene);
		QList<QGraphicsItem*> items = scene->selectedItems();
		VAbstractQGraphicsItem* item = 0;
		if (items.count() == 1)
		{
			item = qgraphicsitem_cast<VAbstractQGraphicsItem*>(items.first());
			if (item != 0)
			{
				if (g_nDragHandle != Handle_None && g_selectMode == SelectToolMode_Size)
				{
					if (opposite_.isNull())
					{
						opposite_ = item->Opposite(g_nDragHandle);
						if (opposite_.x() == 0)
							opposite_.setX(1);
						if (opposite_.y() == 0)
							opposite_.setY(1);
					}
					QPointF new_delta = item->mapFromScene(c_last) - opposite_;
					QPointF initial_delta = item->mapFromScene(c_down) - opposite_;
					double sx = new_delta.x() / initial_delta.x();
					double sy = new_delta.y() / initial_delta.y();
					item->Stretch(g_nDragHandle, sx, sy, opposite_);
					emit scene->Signals_itemResize(item, g_nDragHandle, QPointF(sx, sy));
				}
				else if (g_nDragHandle > Left && g_selectMode == SelectToolMode_Editor)
				{
					item->Control(g_nDragHandle, c_last);
					emit scene->Signals_itemControl(item, g_nDragHandle, c_last, c_down);
				}
				else if (g_nDragHandle == Handle_None)
				{
					int handle = item->CollidesWithHandle(event->scenePos());
					if (handle != Handle_None)
					{
						setCursor(scene, Qt::OpenHandCursor);
						m_hoverSizer = true;
					}
					else
					{
						setCursor(scene, Qt::ArrowCursor);
						m_hoverSizer = false;
					}
				}
			}
		}
		if (g_selectMode == SelectToolMode_Move)
		{
			setCursor(scene, Qt::ClosedHandCursor);
			if (dashRect)
			{
				dashRect->setPos(initialPositions + c_last - c_down);
			}
		}
		if (g_selectMode != SelectToolMode_Size && items.count() > 1)
		{
			scene->MouseEvent(event);
		}
	}

	void VGraphicsSelectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		VGraphicsDrawTool::mouseReleaseEvent(event, scene);
		if (event->button() != Qt::LeftButton) return;
		QList<QGraphicsItem*> items = scene->selectedItems();
		if (items.count() == 1)
		{
			VAbstractQGraphicsItem* item = qgraphicsitem_cast<VAbstractQGraphicsItem*>(items.first());
			if (item != 0 && g_selectMode == SelectToolMode_Move && c_last != c_down)
			{
				item->setPos(initialPositions + c_last - c_down);
				emit scene->Signals_itemMoved(item, c_last - c_down);
			}
			else if (item != 0 && (g_selectMode == SelectToolMode_Size || g_selectMode == SelectToolMode_Editor) && c_last != c_down)
			{
				item->UpdateCoordinate();
			}
		}
		else if (items.count() > 1 && g_selectMode == SelectToolMode_Move && c_last != c_down)
		{
			emit scene->Signals_itemMoved(NULL, c_last - c_down);
		}
		if (g_selectMode == SelectToolMode_NetSelect)
		{
			if (scene->View())
			{
				QGraphicsView* view = scene->View();
				view->setDragMode(QGraphicsView::NoDrag);
			}
		}
		if (dashRect)
		{
			scene->removeItem(dashRect);
			delete dashRect;
			dashRect = 0;
		}
		g_selectMode = SelectToolMode_None;
		g_nDragHandle = Handle_None;
		m_hoverSizer = false;
		opposite_ = QPointF();
		scene->MouseEvent(event);
	}

	VGraphicsRectTool::VGraphicsRectTool(VGraphicsDrawShape drawShape) : VGraphicsDrawTool(drawShape)
	{
	}

	void VGraphicsRectTool::mousePressEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		if (event->button() != Qt::LeftButton) return;
		scene->clearSelection();
		VGraphicsDrawTool::mousePressEvent(event, scene);
		switch (c_drawShape)
		{
		case DrawShape_Rectangle:
			item = new VGraphicsRectItem(QRect(1, 1, 1, 1));
			break;
		case DrawShape_Roundrect:
			item = new VGraphicsRectItem(QRect(1, 1, 1, 1), true);
			break;
		case DrawShape_Ellipse:
			item = new VGraphicsEllipseItem(QRect(1, 1, 1, 1));
			break;
		}
		if (item == 0) return;
		c_down += QPoint(2, 2);
		item->setPos(event->scenePos());
		scene->addItem(item);
		item->setSelected(true);
		item->SetPen(c_pen);
		item->SetBrush(c_brush);
		g_selectMode = SelectToolMode_Size;
		g_nDragHandle = RightBottom;
	}

	void VGraphicsRectTool::mouseMoveEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		setCursor(scene, Qt::CrossCursor);
		s_selectTool.mouseMoveEvent(event, scene);
	}

	void VGraphicsRectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		s_selectTool.mouseReleaseEvent(event, scene);
		if (event->scenePos() == (c_down - QPoint(2, 2)))
		{

			if (item != 0)
			{
				item->setSelected(false);
				scene->removeItem(item);
				delete item;
				item = 0;
			}
		}
		else if (item)
		{
			emit scene->Signals_itemAdded(item);
		}
		c_drawShape = DrawShape_Selection;
	}

	VGraphicsPolygonTool::VGraphicsPolygonTool(VGraphicsDrawShape shape) : VGraphicsDrawTool(shape), m_nPoints(0)
	{
	}

	void VGraphicsPolygonTool::mousePressEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		VGraphicsDrawTool::mousePressEvent(event, scene);
		if (event->button() != Qt::LeftButton) return;
		if (item == nullptr)
		{
			if (c_drawShape == DrawShape_Polygon)
			{
				item = new VGraphicsPolygonItem(nullptr);
			}
			else if (c_drawShape == DrawShape_Bezier)
			{
				item = new VGraphicsBezierItem();
			}
			else if (c_drawShape == DrawShape_Polyline)
			{
				item = new VGraphicsBezierItem(false);
			}
			else if (c_drawShape == DrawShape_Line)
			{
				item = new VGraphicsLineItem(0);
			}
			item->setPos(event->scenePos());
			scene->addItem(item);
			initialPositions = c_down;
			item->AddPoint(c_down);
			item->setSelected(true);
			item->SetPen(c_pen);
			item->SetBrush(c_brush);
			m_nPoints++;
		}
		else if (c_down == c_last)
		{
			/*if (item != NULL)
			{
				scene->removeItem(item);
				delete item;
				item = NULL;
				c_drawShape = selection;
				selectMode = none;
				return;
			}*/
		}
		item->AddPoint(c_down + QPoint(1, 0));
		m_nPoints++;
		g_selectMode = SelectToolMode_Size;
		g_nDragHandle = item->HandleCount();
	}

	void VGraphicsPolygonTool::mouseMoveEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		VGraphicsDrawTool::mouseMoveEvent(event, scene);
		setCursor(scene, Qt::CrossCursor);
		if (item != 0)
		{
			if (g_nDragHandle != Handle_None && g_selectMode == SelectToolMode_Size)
			{
				item->Control(g_nDragHandle, c_last);
			}
		}
	}

	void VGraphicsPolygonTool::mouseReleaseEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene)
	{
		VGraphicsDrawTool::mousePressEvent(event, scene);
		if (event->button() == Qt::RightButton)
		{
			item->EndPoint(event->scenePos());
			item->UpdateCoordinate();
			emit scene->Signals_itemAdded(item);
			item = nullptr;
			g_selectMode = SelectToolMode_None;
			c_drawShape = DrawShape_Selection;
			m_nPoints = 0;
		}
	}
}
