#include "VGraphicsItem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#define VGRAPHICSITEM_PI 3.1415926

namespace VisWindow
{
	static QPainterPath qt_graphicsItem_shapeFromPath(const QPainterPath& path, const QPen& pen)
	{
		// We unfortunately need this hack as QPainterPathStroker will set a width of 1.0
		// if we pass a value of 0.0 to QPainterPathStroker::setWidth()
		const qreal penWidthZero = qreal(0.00000001);

		if (path == QPainterPath() || pen == Qt::NoPen)
			return path;
		QPainterPathStroker ps;
		ps.setCapStyle(pen.capStyle());
		if (pen.widthF() <= 0.0)
			ps.setWidth(penWidthZero);
		else
			ps.setWidth(pen.widthF());
		ps.setJoinStyle(pen.joinStyle());
		ps.setMiterLimit(pen.miterLimit());
		QPainterPath p = ps.createStroke(path);
		p.addPath(path);
		return p;
	}

	static void qt_graphicsItem_highlightSelected(
		QGraphicsItem* item, QPainter* painter, const QStyleOptionGraphicsItem* option)
	{
		const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
		if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
			return;

		const QRectF mbrect = painter->transform().mapRect(item->boundingRect());
		if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
			return;

		qreal itemPenWidth;
		switch (item->type())
		{
		case QGraphicsEllipseItem::Type:
			itemPenWidth = static_cast<QGraphicsEllipseItem*>(item)->pen().widthF();
			break;
		case QGraphicsPathItem::Type:
			itemPenWidth = static_cast<QGraphicsPathItem*>(item)->pen().widthF();
			break;
		case QGraphicsPolygonItem::Type:
			itemPenWidth = static_cast<QGraphicsPolygonItem*>(item)->pen().widthF();
			break;
		case QGraphicsRectItem::Type:
			itemPenWidth = static_cast<QGraphicsRectItem*>(item)->pen().widthF();
			break;
		case QGraphicsSimpleTextItem::Type:
			itemPenWidth = static_cast<QGraphicsSimpleTextItem*>(item)->pen().widthF();
			break;
		case QGraphicsLineItem::Type:
			itemPenWidth = static_cast<QGraphicsLineItem*>(item)->pen().widthF();
			break;
		default:
			itemPenWidth = 1.0;
		}
		const qreal pad = itemPenWidth / 2;

		const qreal penWidth = 0; // cosmetic pen

		const QColor fgcolor = option->palette.windowText().color();
		const QColor bgcolor( // ensure good contrast against fgcolor
							 fgcolor.red() > 127 ? 0 : 255,
							 fgcolor.green() > 127 ? 0 : 255,
							 fgcolor.blue() > 127 ? 0 : 255);


		painter->setPen(QPen(bgcolor, penWidth, Qt::SolidLine));
		painter->setBrush(Qt::NoBrush);
		painter->drawRect(item->boundingRect().adjusted(-pad, -pad, pad, pad));

		painter->setPen(QPen(QColor("lightskyblue"), 0, Qt::SolidLine));
		painter->setBrush(Qt::NoBrush);
		painter->drawRect(item->boundingRect().adjusted(-pad, -pad, pad, pad));

	}


	VGraphicsItem::VGraphicsItem(QGraphicsItem* parent, bool _bEnableHandles)
	{
		m_vpControlBlock.reserve(Left);
		for (int i = LeftTop; i <= Left; ++i)
		{
			VGraphicsItemControlBlock* pControl = new VGraphicsItemControlBlock(this, i);
			m_vpControlBlock.push_back(pControl);
		}

		setFlag(QGraphicsItem::ItemIsMovable, true);
		setFlag(QGraphicsItem::ItemIsSelectable, true);
		setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
		this->setAcceptHoverEvents(true);
	}

	int VGraphicsItem::type() const
	{
		return eVGraphicsItemType_Base;
	}

	bool VGraphicsItem::LoadFromXml(QXmlStreamReader* xml)
	{
		qreal x = xml->attributes().value(tr("x")).toDouble();
		qreal y = xml->attributes().value(tr("y")).toDouble();
		m_width = xml->attributes().value("width").toDouble();
		m_height = xml->attributes().value("height").toDouble();
		setZValue(xml->attributes().value("z").toDouble());
		setRotation(xml->attributes().value("rotate").toDouble());
		setPos(x, y);
		return true;
	}
	bool VGraphicsItem::SaveToXml(QXmlStreamWriter* xml)
	{
		xml->writeAttribute(tr("rotate"), QString("%1").arg(rotation()));
		xml->writeAttribute(tr("x"), QString("%1").arg(pos().x()));
		xml->writeAttribute(tr("y"), QString("%1").arg(pos().y()));
		xml->writeAttribute(tr("z"), QString("%1").arg(zValue()));
		xml->writeAttribute(tr("width"), QString("%1").arg(m_width));
		xml->writeAttribute(tr("height"), QString("%1").arg(m_height));
		return true;
	}

	void VGraphicsItem::Updatehandles()
	{
		const QRectF& geom = this->boundingRect();

		const std::vector<VGraphicsItemControlBlock*>::iterator hend = m_vpControlBlock.end();
		for (std::vector<VGraphicsItemControlBlock*>::iterator it = m_vpControlBlock.begin(); it != hend; ++it)
		{
			VGraphicsItemControlBlock* hndl = *it;;
			switch (hndl->Dir())
			{
			case LeftTop:
				hndl->Move(geom.x(), geom.y());
				break;
			case Top:
				hndl->Move(geom.x() + geom.width() / 2, geom.y());
				break;
			case RightTop:
				hndl->Move(geom.x() + geom.width(), geom.y());
				break;
			case Right:
				hndl->Move(geom.x() + geom.width(), geom.y() + geom.height() / 2);
				break;
			case RightBottom:
				hndl->Move(geom.x() + geom.width(), geom.y() + geom.height());
				break;
			case Bottom:
				hndl->Move(geom.x() + geom.width() / 2, geom.y() + geom.height());
				break;
			case LeftBottom:
				hndl->Move(geom.x(), geom.y() + geom.height());
				break;
			case Left:
				hndl->Move(geom.x(), geom.y() + geom.height() / 2);
				break;
			default:
				break;
			}
		}
	}

	QVariant VGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
	{
		if (change == QGraphicsItem::ItemSelectedHasChanged)
		{
			QGraphicsItemGroup* g = dynamic_cast<QGraphicsItemGroup*>(parentItem());
			if (!g)
				SetState(value.toBool() ? SelectionHandleActive : SelectionHandleOff);
			else
			{
				setSelected(false);
				return QVariant::fromValue<bool>(false);
			}
		}
		return QGraphicsItem::itemChange(change, value);
	}

	void VGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
	{
		Q_UNUSED(event);
	}

	class VGraphicsRectItemPrivate
	{
	public:
		VGraphicsRectItemPrivate(const QRect& rect, bool isRound = false) : m_isRound(isRound), m_fRatioX(1 / 10.0), m_fRatioY(1 / 3.0)
		{
			m_initialRect = rect;
			m_originPoint = QPointF(0, 0);
		}
		bool m_isRound;
		qreal m_fRatioY;
		qreal m_fRatioX;
		QRectF m_initialRect;
		QPointF opposite_;
		QPointF m_originPoint;
	};

	VGraphicsRectItem::VGraphicsRectItem(const QRect& rect, bool isRound, QGraphicsItem* parent)
		: VGraphicsItem(parent)
		, m_pVGraphicsRectItemPrivate(new VGraphicsRectItemPrivate(rect, isRound))
	{
		m_width = rect.width();
		m_height = rect.height();
		m_localRect = rect;
		Updatehandles();
		if (m_pVGraphicsRectItemPrivate->m_isRound)
		{
			VGraphicsItemControlBlock* pContorlBlock = new VGraphicsItemControlBlock(this, 9, true);
			m_vpControlBlock.push_back(pContorlBlock);
			pContorlBlock = new VGraphicsItemControlBlock(this, 10, true);
			m_vpControlBlock.push_back(pContorlBlock);
		}
	}

	VGraphicsRectItem::~VGraphicsRectItem()
	{
		if (m_pVGraphicsRectItemPrivate)
		{
			delete m_pVGraphicsRectItemPrivate;
		}
	}

	QPainterPath VGraphicsRectItem::shape() const
	{
		QPainterPath path;
		double rx, ry;
		if (m_pVGraphicsRectItemPrivate->m_fRatioX <= 0)
			rx = 0;
		else
		{
			rx = m_width * m_pVGraphicsRectItemPrivate->m_fRatioX + 0.5;
		}
		if (m_pVGraphicsRectItemPrivate->m_fRatioY <= 0)
			ry = 0;
		else
			ry = m_height * m_pVGraphicsRectItemPrivate->m_fRatioY + 0.5;
		if (m_pVGraphicsRectItemPrivate->m_isRound)
			path.addRoundedRect(Rect(), rx, ry);
		else
			path.addRect(Rect());
		return path;
	}

	int VGraphicsRectItem::type() const
	{
		return eVGraphicsItemType_Rect;
	}

	void VGraphicsRectItem::Control(int dir, const QPointF& delta)
	{
		QPointF local = mapFromParent(delta);
		switch (dir)
		{
		case 9:
		{
			QRectF delta1 = Rect();
			int y = local.y();
			if (y > delta1.center().y())
				y = delta1.center().y();
			if (y < delta1.top())
				y = delta1.top();
			int H = delta1.height();
			if (H == 0)
				H = 1;
			m_pVGraphicsRectItemPrivate->m_fRatioY = std::abs(((float)(delta1.top() - y))) / H;
		}
		break;
		case 10:
		{
			QRectF delta1 = Rect();
			int x = local.x();
			if (x < delta1.center().x())
				x = delta1.center().x();
			if (x > delta1.right())
				x = delta1.right();
			int W = delta1.width();
			if (W == 0)
				W = 1;
			m_pVGraphicsRectItemPrivate->m_fRatioX = std::abs(((float)(delta1.right() - x))) / W;
			break;
		}
		case 11:
		{
			m_pVGraphicsRectItemPrivate->m_originPoint = local;
		}
		break;
		default:
			break;
		}
		prepareGeometryChange();
		Updatehandles();
	}

	void VGraphicsRectItem::Stretch(int handle, double sx, double sy, const QPointF& origin)
	{
		QTransform trans;
		switch (handle)
		{
		case Right:
		case Left:
			sy = 1;
			break;
		case Top:
		case Bottom:
			sx = 1;
			break;
		default:
			break;
		}

		m_pVGraphicsRectItemPrivate->opposite_ = origin;

		trans.translate(origin.x(), origin.y());
		trans.scale(sx, sy);
		trans.translate(-origin.x(), -origin.y());

		prepareGeometryChange();
		m_localRect = trans.mapRect(m_pVGraphicsRectItemPrivate->m_initialRect);
		m_width = m_localRect.width();
		m_height = m_localRect.height();
		Updatehandles();
	}

	QRectF VGraphicsRectItem::Rect() const
	{
		return m_localRect;
	}

	void VGraphicsRectItem::UpdateCoordinate()
	{
		QPointF pt1, pt2, delta;

		pt1 = mapToScene(transformOriginPoint());
		pt2 = mapToScene(m_localRect.center());
		delta = pt1 - pt2;

		if (!parentItem())
		{
			prepareGeometryChange();
			m_localRect = QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
			m_width = m_localRect.width();
			m_height = m_localRect.height();
			setTransform(transform().translate(delta.x(), delta.y()));
			setTransformOriginPoint(m_localRect.center());
			moveBy(-delta.x(), -delta.y());
			setTransform(transform().translate(-delta.x(), -delta.y()));
			m_pVGraphicsRectItemPrivate->opposite_ = QPointF(0, 0);
			Updatehandles();
		}
		m_pVGraphicsRectItemPrivate->m_initialRect = m_localRect;
	}

	void VGraphicsRectItem::Move(const QPointF& point)
	{
		moveBy(point.x(), point.y());
	}

	QGraphicsItem* VGraphicsRectItem::Duplicate() const
	{
		VGraphicsRectItem* item = new VGraphicsRectItem(Rect().toRect(), m_pVGraphicsRectItemPrivate->m_isRound);
		item->m_width = Width();
		item->m_height = Height();
		item->setPos(pos().x(), pos().y());
		item->SetPen(Pen());
		item->SetBrush(Brush());
		item->setTransform(transform());
		item->setTransformOriginPoint(transformOriginPoint());
		item->setRotation(rotation());
		item->setScale(scale());
		item->setZValue(zValue() + 0.1);
		item->m_pVGraphicsRectItemPrivate->m_fRatioY = m_pVGraphicsRectItemPrivate->m_fRatioY;
		item->m_pVGraphicsRectItemPrivate->m_fRatioX = m_pVGraphicsRectItemPrivate->m_fRatioX;
		item->UpdateCoordinate();
		return item;
	}

	QString VGraphicsRectItem::DisplayName() const
	{
		return tr("rectangle");
	}

	bool VGraphicsRectItem::LoadFromXml(QXmlStreamReader* xml)
	{
		m_pVGraphicsRectItemPrivate->m_isRound = (xml->name() == tr("roundrect"));
		if (m_pVGraphicsRectItemPrivate->m_isRound)
		{
			m_pVGraphicsRectItemPrivate->m_fRatioX = xml->attributes().value(tr("rx")).toDouble();
			m_pVGraphicsRectItemPrivate->m_fRatioY = xml->attributes().value(tr("ry")).toDouble();
		}
		VGraphicsItem::LoadFromXml(xml);
		UpdateCoordinate();
		xml->skipCurrentElement();
		return true;
	}

	bool VGraphicsRectItem::SaveToXml(QXmlStreamWriter* xml)
	{
		if (m_pVGraphicsRectItemPrivate->m_isRound)
		{
			xml->writeStartElement(tr("roundrect"));
			xml->writeAttribute(tr("rx"), QString("%1").arg(m_pVGraphicsRectItemPrivate->m_fRatioX));
			xml->writeAttribute(tr("ry"), QString("%1").arg(m_pVGraphicsRectItemPrivate->m_fRatioY));
		}
		else
			xml->writeStartElement(tr("rect"));

		VGraphicsItem::SaveToXml(xml);
		xml->writeEndElement();
		return true;
	}

	QRectF VGraphicsRectItem::boundingRect() const
	{
		return m_localRect;
	}

	void VGraphicsRectItem::Updatehandles()
	{
		const QRectF& geom = this->boundingRect();
		VGraphicsItem::Updatehandles();
		if (m_pVGraphicsRectItemPrivate->m_isRound)
		{
			m_vpControlBlock[8]->Move(geom.right(), geom.top() + geom.height() * m_pVGraphicsRectItemPrivate->m_fRatioY);
			m_vpControlBlock[9]->Move(geom.right() - geom.width() * m_pVGraphicsRectItemPrivate->m_fRatioX, geom.top());
		}
	}

	void VGraphicsRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{

		painter->setPen(Pen());
		painter->setBrush(Brush());
		double rx, ry;
		if (m_pVGraphicsRectItemPrivate->m_fRatioX <= 0)
			rx = 0;
		else
		{
			rx = m_width * m_pVGraphicsRectItemPrivate->m_fRatioX + 0.5;
		}
		if (m_pVGraphicsRectItemPrivate->m_fRatioY <= 0)
			ry = 0;
		else
			ry = m_height * m_pVGraphicsRectItemPrivate->m_fRatioY + 0.5;
		if (m_pVGraphicsRectItemPrivate->m_isRound)
			painter->drawRoundedRect(Rect(), rx, ry);
		else
			painter->drawRect(Rect().toRect());

		painter->setPen(Qt::blue);
		painter->drawLine(QLine(QPoint(m_pVGraphicsRectItemPrivate->opposite_.x() - 6, m_pVGraphicsRectItemPrivate->opposite_.y()), QPoint(m_pVGraphicsRectItemPrivate->opposite_.x() + 6, m_pVGraphicsRectItemPrivate->opposite_.y())));
		painter->drawLine(QLine(QPoint(m_pVGraphicsRectItemPrivate->opposite_.x(), m_pVGraphicsRectItemPrivate->opposite_.y() - 6), QPoint(m_pVGraphicsRectItemPrivate->opposite_.x(), m_pVGraphicsRectItemPrivate->opposite_.y() + 6)));


		if (option->state & QStyle::State_Selected)
			qt_graphicsItem_highlightSelected(this, painter, option);
	}

	class VGraphicsEllipseItemPrivate
	{
	public:
		VGraphicsEllipseItemPrivate() :m_startAngle(40), m_spanAngle(400)
		{
		}
		int m_startAngle;
		int m_spanAngle;
	};

	VGraphicsEllipseItem::VGraphicsEllipseItem(const QRect& rect, QGraphicsItem* parent) : VGraphicsRectItem(rect, parent), m_pVGraphicsEllipseItemPrivate(new VGraphicsEllipseItemPrivate)
	{
		VGraphicsItemControlBlock* pControlBlock = new VGraphicsItemControlBlock(this, 9, true);
		m_vpControlBlock.push_back(pControlBlock);
		pControlBlock = new VGraphicsItemControlBlock(this, 10, true);
		m_vpControlBlock.push_back(pControlBlock);
		Updatehandles();
	}

	VGraphicsEllipseItem::~VGraphicsEllipseItem()
	{
		if (m_pVGraphicsEllipseItemPrivate)
		{
			delete m_pVGraphicsEllipseItemPrivate;
		}
	}

	QPainterPath VGraphicsEllipseItem::shape() const
	{
		QPainterPath path;
		int startAngle = m_pVGraphicsEllipseItemPrivate->m_startAngle <= m_pVGraphicsEllipseItemPrivate->m_spanAngle ? m_pVGraphicsEllipseItemPrivate->m_startAngle : m_pVGraphicsEllipseItemPrivate->m_spanAngle;
		int endAngle = m_pVGraphicsEllipseItemPrivate->m_startAngle >= m_pVGraphicsEllipseItemPrivate->m_spanAngle ? m_pVGraphicsEllipseItemPrivate->m_startAngle : m_pVGraphicsEllipseItemPrivate->m_spanAngle;
		if (endAngle - startAngle > 360)
			endAngle = startAngle + 360;

		if (m_localRect.isNull())
			return path;
		if ((endAngle - startAngle) % 360 != 0)
		{
			path.moveTo(m_localRect.center());
			path.arcTo(m_localRect, startAngle, endAngle - startAngle);
		}
		else
		{
			path.addEllipse(m_localRect);
		}
		path.closeSubpath();
		return path;
	}

	int VGraphicsEllipseItem::type() const
	{
		return eVGraphicsItemType_Ellipse;
	}

	void VGraphicsEllipseItem::Control(int dir, const QPointF& delta)
	{
		QPointF local = mapFromScene(delta);

		switch (dir)
		{
		case 9:
		{
			qreal len_y = local.y() - m_localRect.center().y();
			qreal len_x = local.x() - m_localRect.center().x();
			m_pVGraphicsEllipseItemPrivate->m_startAngle = -atan2(len_y, len_x) * 180 / VGRAPHICSITEM_PI;
		}
		break;
		case 10:
		{
			qreal len_y = local.y() - m_localRect.center().y();
			qreal len_x = local.x() - m_localRect.center().x();
			m_pVGraphicsEllipseItemPrivate->m_spanAngle = -atan2(len_y, len_x) * 180 / VGRAPHICSITEM_PI;
			break;
		}
		default:
			break;
		}
		prepareGeometryChange();
		if (m_pVGraphicsEllipseItemPrivate->m_startAngle > m_pVGraphicsEllipseItemPrivate->m_spanAngle)
			m_pVGraphicsEllipseItemPrivate->m_startAngle -= 360;
		if (m_pVGraphicsEllipseItemPrivate->m_spanAngle < m_pVGraphicsEllipseItemPrivate->m_startAngle)
		{
			qreal tmp = m_pVGraphicsEllipseItemPrivate->m_spanAngle;
			m_pVGraphicsEllipseItemPrivate->m_spanAngle = m_pVGraphicsEllipseItemPrivate->m_startAngle;
			m_pVGraphicsEllipseItemPrivate->m_startAngle = tmp;
		}
		if (qAbs(m_pVGraphicsEllipseItemPrivate->m_spanAngle - m_pVGraphicsEllipseItemPrivate->m_startAngle) > 360)
		{
			m_pVGraphicsEllipseItemPrivate->m_startAngle = 40;
			m_pVGraphicsEllipseItemPrivate->m_spanAngle = 400;
		}
		Updatehandles();
	}

	QGraphicsItem* VGraphicsEllipseItem::Duplicate() const
	{
		VGraphicsEllipseItem* item = new VGraphicsEllipseItem(m_localRect.toRect());
		item->m_width = Width();
		item->m_height = Height();
		item->m_pVGraphicsEllipseItemPrivate->m_startAngle = m_pVGraphicsEllipseItemPrivate->m_startAngle;
		item->m_pVGraphicsEllipseItemPrivate->m_spanAngle = m_pVGraphicsEllipseItemPrivate->m_spanAngle;
		item->setPos(pos().x(), pos().y());
		item->SetPen(Pen());
		item->SetBrush(Brush());
		item->setTransform(transform());
		item->setTransformOriginPoint(transformOriginPoint());
		item->setRotation(rotation());
		item->setScale(scale());
		item->setZValue(zValue() + 0.1);
		item->UpdateCoordinate();
		return item;
	}

	QString VGraphicsEllipseItem::DisplayName() const
	{
		return tr("ellipse");
	}

	bool VGraphicsEllipseItem::LoadFromXml(QXmlStreamReader* xml)
	{
		m_pVGraphicsEllipseItemPrivate->m_startAngle = xml->attributes().value("startAngle").toInt();
		m_pVGraphicsEllipseItemPrivate->m_spanAngle = xml->attributes().value("spanAngle").toInt();
		VGraphicsItem::LoadFromXml(xml);
		xml->skipCurrentElement();
		UpdateCoordinate();
		return true;
	}

	bool VGraphicsEllipseItem::SaveToXml(QXmlStreamWriter* xml)
	{
		xml->writeStartElement(tr("ellipse"));
		xml->writeAttribute("startAngle", QString("%1").arg(m_pVGraphicsEllipseItemPrivate->m_startAngle));
		xml->writeAttribute("spanAngle", QString("%1").arg(m_pVGraphicsEllipseItemPrivate->m_spanAngle));
		VGraphicsItem::SaveToXml(xml);
		xml->writeEndElement();
		return true;
	}

    QRectF VGraphicsEllipseItem::boundingRect() const
    {
        return shape().controlPointRect();
    }

	void VGraphicsEllipseItem::Updatehandles()
	{
		VGraphicsItem::Updatehandles();
		QRectF local = QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
		QPointF delta = local.center() - m_localRect.center();
		qreal x = (m_width / 2) * cos(-m_pVGraphicsEllipseItemPrivate->m_startAngle * VGRAPHICSITEM_PI / 180);
		qreal y = (m_height / 2) * sin(-m_pVGraphicsEllipseItemPrivate->m_startAngle * VGRAPHICSITEM_PI / 180);
		m_vpControlBlock.at(8)->Move(x - delta.x(), y - delta.y());
		x = (m_width / 2) * cos(-m_pVGraphicsEllipseItemPrivate->m_spanAngle * VGRAPHICSITEM_PI / 180);
		y = (m_height / 2) * sin(-m_pVGraphicsEllipseItemPrivate->m_spanAngle * VGRAPHICSITEM_PI / 180);
		m_vpControlBlock.at(9)->Move(x - delta.x(), y - delta.y());
	}

	void VGraphicsEllipseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(option);
		Q_UNUSED(widget);
		QColor c = BrushColor();
		QRectF rc = m_localRect;
		qreal radius = qMax(rc.width(), rc.height());
		painter->setPen(Pen());
		QBrush b(c);
		painter->setBrush(b);
		int startAngle = m_pVGraphicsEllipseItemPrivate->m_startAngle <= m_pVGraphicsEllipseItemPrivate->m_spanAngle ? m_pVGraphicsEllipseItemPrivate->m_startAngle : m_pVGraphicsEllipseItemPrivate->m_spanAngle;
		int endAngle = m_pVGraphicsEllipseItemPrivate->m_startAngle >= m_pVGraphicsEllipseItemPrivate->m_spanAngle ? m_pVGraphicsEllipseItemPrivate->m_startAngle : m_pVGraphicsEllipseItemPrivate->m_spanAngle;
		if (endAngle - startAngle > 360)
			endAngle = startAngle + 360;
		if (qAbs(endAngle - startAngle) % (360) == 0)
			painter->drawEllipse(m_localRect);
		else
			painter->drawPie(m_localRect, startAngle * 16, (endAngle - startAngle) * 16);
		if (option->state & QStyle::State_Selected)
			qt_graphicsItem_highlightSelected(this, painter, option);
	}

	VGraphicsPolygonItem::VGraphicsPolygonItem(QGraphicsItem* parent) : VGraphicsItem(parent)
	{
		m_points.clear();
		m_pen = QPen(Qt::black);
	}

	QPainterPath VGraphicsPolygonItem::shape() const
	{
		QPainterPath path;
		path.addPolygon(m_points);
		path.closeSubpath();
		return qt_graphicsItem_shapeFromPath(path, Pen());
	}

	QPolygonF VGraphicsPolygonItem::Polygon() const
	{
		return m_points;
	}

	int VGraphicsPolygonItem::type() const
	{
		return eVGraphicsItemType_Polygon;
	}

	void VGraphicsPolygonItem::AddPoint(const QPointF& point)
	{
		m_points.append(mapFromScene(point));
		int dir = m_points.count();
		VGraphicsItemControlBlock* pControlBlock = new VGraphicsItemControlBlock(this, dir + Left, true);
		pControlBlock->SetState(SelectionHandleActive);
		m_vpControlBlock.push_back(pControlBlock);
	}

	void VGraphicsPolygonItem::EndPoint(const QPointF& point)
	{
		Q_UNUSED(point);
		int nPoints = m_points.count();
		if (nPoints > 2 && (m_points[nPoints - 1] == m_points[nPoints - 2] ||
							m_points[nPoints - 1].x() - 1 == m_points[nPoints - 2].x() &&
							m_points[nPoints - 1].y() == m_points[nPoints - 2].y()))
		{
			delete m_vpControlBlock[Left + nPoints - 1];
			m_points.remove(nPoints - 1);
			m_vpControlBlock.resize(Left + nPoints - 1);
		}
		m_initialPoints = m_points;
	}

	void VGraphicsPolygonItem::Control(int dir, const QPointF& delta)
	{
		QPointF pt = mapFromScene(delta);
		if (dir <= Left) return;
		m_points[dir - Left - 1] = pt;
		prepareGeometryChange();
		m_localRect = m_points.boundingRect();
		m_width = m_localRect.width();
		m_height = m_localRect.height();
		m_initialPoints = m_points;
		Updatehandles();
	}

	void VGraphicsPolygonItem::Stretch(int handle, double sx, double sy, const QPointF& origin)
	{
		QTransform trans;
		switch (handle)
		{
		case Right:
		case Left:
			sy = 1;
			break;
		case Top:
		case Bottom:
			sx = 1;
			break;
		default:
			break;
		}
		trans.translate(origin.x(), origin.y());
		trans.scale(sx, sy);
		trans.translate(-origin.x(), -origin.y());

		prepareGeometryChange();
		m_points = trans.map(m_initialPoints);
		m_localRect = m_points.boundingRect();
		m_width = m_localRect.width();
		m_height = m_localRect.height();
		Updatehandles();
	}

	void VGraphicsPolygonItem::UpdateCoordinate()
	{
		QPointF pt1, pt2, delta;
		QPolygonF pts = mapToScene(m_points);
		if (parentItem() == NULL)
		{
			pt1 = mapToScene(transformOriginPoint());
			pt2 = mapToScene(boundingRect().center());
			delta = pt1 - pt2;

			for (int i = 0; i < pts.count(); ++i)
				pts[i] += delta;

			prepareGeometryChange();

			m_points = mapFromScene(pts);
			m_localRect = m_points.boundingRect();
			m_width = m_localRect.width();
			m_height = m_localRect.height();
			setTransform(transform().translate(delta.x(), delta.y()));
			moveBy(-delta.x(), -delta.y());
			setTransform(transform().translate(-delta.x(), -delta.y()));
			Updatehandles();
		}
		m_initialPoints = m_points;
	}

	bool VGraphicsPolygonItem::LoadFromXml(QXmlStreamReader* xml)
	{
		VGraphicsItem::LoadFromXml(xml);
		while (xml->readNextStartElement())
		{
			if (xml->name() == "point")
			{
				qreal x = xml->attributes().value("x").toDouble();
				qreal y = xml->attributes().value("y").toDouble();
				m_points.append(QPointF(x, y));
				int dir = m_points.count();
				VGraphicsItemControlBlock* pControlBlock = new VGraphicsItemControlBlock(this, dir + Left, true);
				m_vpControlBlock.push_back(pControlBlock);
				xml->skipCurrentElement();
			}
			else
				xml->skipCurrentElement();
		}
		UpdateCoordinate();
		return true;
	}

	bool VGraphicsPolygonItem::SaveToXml(QXmlStreamWriter* xml)
	{
		xml->writeStartElement("polygon");
		VGraphicsItem::SaveToXml(xml);
		for (int i = 0; i < m_points.count(); ++i)
		{
			xml->writeStartElement("point");
			xml->writeAttribute("x", QString("%1").arg(m_points[i].x()));
			xml->writeAttribute("y", QString("%1").arg(m_points[i].y()));
			xml->writeEndElement();
		}
		xml->writeEndElement();
		return true;
	}

	QString VGraphicsPolygonItem::DisplayName() const
	{
		return tr("polygon");
	}

	QGraphicsItem* VGraphicsPolygonItem::Duplicate() const
	{
		VGraphicsPolygonItem* item = new VGraphicsPolygonItem();
		item->m_width = Width();
		item->m_height = Height();
		item->m_points = m_points;

		for (int i = 0; i < m_points.size(); ++i)
		{
			item->m_vpControlBlock.push_back(new VGraphicsItemControlBlock(item, Left + i + 1, true));
		}
		item->setPos(pos().x(), pos().y());
		item->SetPen(Pen());
		item->SetBrush(Brush());
		item->setTransform(transform());
		item->setTransformOriginPoint(transformOriginPoint());
		item->setRotation(rotation());
		item->setScale(scale());
		item->setZValue(zValue() + 0.1);
		item->UpdateCoordinate();
		return item;
	}

	QRectF VGraphicsPolygonItem::boundingRect() const
	{
		return shape().controlPointRect();
	}

	void VGraphicsPolygonItem::Updatehandles()
	{
		VGraphicsItem::Updatehandles();

		for (int i = 0; i < m_points.size(); ++i)
		{
			m_vpControlBlock[Left + i]->Move(m_points[i].x(), m_points[i].y());
		}
	}

	void VGraphicsPolygonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(option);
		Q_UNUSED(widget);
		painter->setBrush(Brush());
		painter->setPen(Pen());
		painter->drawPolygon(m_points);
		if (option->state & QStyle::State_Selected)
			qt_graphicsItem_highlightSelected(this, painter, option);
	}

	VGraphicsLineItem::VGraphicsLineItem(QGraphicsItem* parent) : VGraphicsPolygonItem(parent)
	{
		m_pen = QPen(Qt::black);
		m_vpControlBlock.reserve(Left);
		std::vector<VGraphicsItemControlBlock*>::iterator hend = m_vpControlBlock.end();
		for (std::vector<VGraphicsItemControlBlock*>::iterator it = m_vpControlBlock.begin(); it != hend; ++it)
			delete (*it);
		m_vpControlBlock.clear();
	}

	QPainterPath VGraphicsLineItem::shape() const
	{
		QPainterPath path;
		if (m_points.size() > 1)
		{
			path.moveTo(m_points.at(0));
			path.lineTo(m_points.at(1));
		}
		return qt_graphicsItem_shapeFromPath(path, Pen());
	}

	int VGraphicsLineItem::type() const
	{
		return eVGraphicsItemType_Line;
	}

	QGraphicsItem* VGraphicsLineItem::Duplicate() const
	{
		VGraphicsLineItem* item = new VGraphicsLineItem();
		item->m_width = Width();
		item->m_height = Height();
		item->m_points = m_points;
		item->m_initialPoints = m_initialPoints;
		item->setPos(pos().x(), pos().y());
		item->SetPen(Pen());
		item->SetBrush(Brush());
		item->setTransform(transform());
		item->setTransformOriginPoint(transformOriginPoint());
		item->setRotation(rotation());
		item->setScale(scale());
		item->setZValue(zValue() + 0.1);
		item->UpdateCoordinate();
		return item;
	}

	void VGraphicsLineItem::AddPoint(const QPointF& point)
	{
		m_points.append(mapFromScene(point));
		int dir = m_points.count();
		VGraphicsItemControlBlock* shr = new VGraphicsItemControlBlock(this, dir + Left, dir == 1 ? false : true);
		shr->SetState(SelectionHandleActive);
		m_vpControlBlock.push_back(shr);
	}

	void VGraphicsLineItem::EndPoint(const QPointF& point)
	{
		Q_UNUSED(point);
		int nPoints = m_points.count();
		if (nPoints > 2 && (m_points[nPoints - 1] == m_points[nPoints - 2] ||
							m_points[nPoints - 1].x() - 1 == m_points[nPoints - 2].x() &&
							m_points[nPoints - 1].y() == m_points[nPoints - 2].y()))
		{
			delete m_vpControlBlock[nPoints - 1];
			m_points.remove(nPoints - 1);
			m_vpControlBlock.resize(nPoints - 1);
		}
		m_initialPoints = m_points;
	}

	QPointF VGraphicsLineItem::Opposite(int handle)
	{
		QPointF pt;
		switch (handle)
		{
		case Right:
		case Left:
		case Top:
		case LeftTop:
		case RightTop:
			pt = m_vpControlBlock[1]->pos();
			break;
		case RightBottom:
		case LeftBottom:
		case Bottom:
			pt = m_vpControlBlock[0]->pos();
			break;
		}
		return pt;
	}

	void VGraphicsLineItem::UpdateCoordinate()
	{
		m_initialPoints = m_points;
	}

	int VGraphicsLineItem::HandleCount() const
	{
		return m_vpControlBlock.size() + Left;
	}

	void VGraphicsLineItem::Stretch(int handle, double sx, double sy, const QPointF& origin)
	{
		QTransform trans;
		switch (handle)
		{
		case Right:
		case Left:
			sy = 1;
			break;
		case Top:
		case Bottom:
			sx = 1;
			break;
		default:
			break;
		}
		trans.translate(origin.x(), origin.y());
		trans.scale(sx, sy);
		trans.translate(-origin.x(), -origin.y());

		prepareGeometryChange();
		m_points = trans.map(m_initialPoints);
		m_localRect = m_points.boundingRect();
		m_width = m_localRect.width();
		m_height = m_localRect.height();
		Updatehandles();
	}

	bool VGraphicsLineItem::LoadFromXml(QXmlStreamReader* xml)
	{
		VGraphicsItem::LoadFromXml(xml);
		while (xml->readNextStartElement())
		{
			if (xml->name() == "point")
			{
				qreal x = xml->attributes().value("x").toDouble();
				qreal y = xml->attributes().value("y").toDouble();
				m_points.append(QPointF(x, y));
				int dir = m_points.count();
				VGraphicsItemControlBlock* shr = new VGraphicsItemControlBlock(this, dir + Left, dir == 1 ? false : true);
				m_vpControlBlock.push_back(shr);
				xml->skipCurrentElement();
			}
			else
				xml->skipCurrentElement();
		}
		Updatehandles();
		return true;
	}

	bool VGraphicsLineItem::SaveToXml(QXmlStreamWriter* xml)
	{
		xml->writeStartElement("line");
		VGraphicsItem::SaveToXml(xml);
		for (int i = 0; i < m_points.count(); ++i)
		{
			xml->writeStartElement("point");
			xml->writeAttribute("x", QString("%1").arg(m_points[i].x()));
			xml->writeAttribute("y", QString("%1").arg(m_points[i].y()));
			xml->writeEndElement();
		}
		xml->writeEndElement();
		return true;
	}

	QString VGraphicsLineItem::DisplayName() const
	{
		return tr("line");
	}

	void VGraphicsLineItem::Updatehandles()
	{
		for (int i = 0; i < m_points.size(); ++i)
		{
			m_vpControlBlock[i]->Move(m_points[i].x(), m_points[i].y());
		}
	}

	void VGraphicsLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(option);
		Q_UNUSED(widget);
		painter->setPen(Pen());
		if (m_points.size() > 1)
			painter->drawLine(m_points.at(0), m_points.at(1));
	}

	VGraphicsBezierItem::VGraphicsBezierItem(bool bbezier, QGraphicsItem* parent) :VGraphicsPolygonItem(parent), m_isBezier(bbezier)
	{
		m_brush = QBrush(Qt::NoBrush);
	}

	QPainterPath VGraphicsBezierItem::shape() const
	{
		QPainterPath path;
		path.moveTo(m_points.at(0));
		int i = 1;
		while (m_isBezier && (i + 2 < m_points.size()))
		{
			path.cubicTo(m_points.at(i), m_points.at(i + 1), m_points.at(i + 2));
			i += 3;
		}
		while (i < m_points.size())
		{
			path.lineTo(m_points.at(i));
			++i;
		}

		return qt_graphicsItem_shapeFromPath(path, Pen());
	}

	int VGraphicsBezierItem::type() const
	{
		return eVGraphicsItemType_Bezier;
	}

	QGraphicsItem* VGraphicsBezierItem::Duplicate() const
	{
		VGraphicsBezierItem* item = new VGraphicsBezierItem();
		item->m_width = Width();
		item->m_height = Height();
		item->m_points = m_points;
		item->m_isBezier = m_isBezier;
		for (int i = 0; i < m_points.size(); ++i)
		{
			item->m_vpControlBlock.push_back(new VGraphicsItemControlBlock(item, Left + i + 1, true));
		}
		item->setPos(pos().x(), pos().y());
		item->SetPen(Pen());
		item->SetBrush(Brush());
		item->setTransform(transform());
		item->setTransformOriginPoint(transformOriginPoint());
		item->setRotation(rotation());
		item->setScale(scale());
		item->setZValue(zValue() + 0.1);
		item->UpdateCoordinate();
		return item;
	}

	bool VGraphicsBezierItem::LoadFromXml(QXmlStreamReader* xml)
	{
		m_isBezier = (xml->name() == tr("bezier"));
		return VGraphicsPolygonItem::LoadFromXml(xml);
	}

	bool VGraphicsBezierItem::SaveToXml(QXmlStreamWriter* xml)
	{
		if (m_isBezier)
			xml->writeStartElement("bezier");
		else
			xml->writeStartElement("polyline");

		VGraphicsItem::SaveToXml(xml);

		for (int i = 0; i < m_points.count(); ++i)
		{
			xml->writeStartElement("point");
			xml->writeAttribute("x", QString("%1").arg(m_points[i].x()));
			xml->writeAttribute("y", QString("%1").arg(m_points[i].y()));
			xml->writeEndElement();
		}
		xml->writeEndElement();
		return true;
	}

	QString VGraphicsBezierItem::DisplayName() const
	{
		return tr("bezier");
	}

	void VGraphicsBezierItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(option);
		Q_UNUSED(widget);

		QPainterPath path;
		painter->setPen(Pen());
		painter->setBrush(Brush());
		path.moveTo(m_points.at(0));

		int i = 1;
		while (m_isBezier && (i + 2 < m_points.size()))
		{
			path.cubicTo(m_points.at(i), m_points.at(i + 1), m_points.at(i + 2));
			i += 3;
		}
		while (i < m_points.size())
		{
			path.lineTo(m_points.at(i));
			++i;
		}
		painter->drawPath(path);

		if (option->state & QStyle::State_Selected)
		{
			painter->setPen(QPen(Qt::lightGray, 0, Qt::SolidLine));
			painter->setBrush(Qt::NoBrush);
			painter->drawPolyline(m_points);
		}

		if (option->state & QStyle::State_Selected)
			qt_graphicsItem_highlightSelected(this, painter, option);
	}

	class VGraphicsItemGroupPrivate
	{
	public:
		VGraphicsItemGroupPrivate(QGraphicsItem* parent) : m_parent(parent)
		{
		}
		~VGraphicsItemGroupPrivate()
		{
		}
		QGraphicsItem* m_parent;
		QRectF m_itemsBoundingRect;
		QRectF m_initialRect;
	};

	VGraphicsItemGroup::VGraphicsItemGroup(QGraphicsItem* parent) :VAbstractGraphicsItem <QGraphicsItemGroup>(parent), m_pVGraphicsItemGroupPrivate(new VGraphicsItemGroupPrivate(parent))
	{
		m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect = QRectF();
		m_vpControlBlock.reserve(Left);
		for (int i = LeftTop; i <= Left; ++i)
		{
			VGraphicsItemControlBlock* pControlBlock = new VGraphicsItemControlBlock(this, i);
			m_vpControlBlock.push_back(pControlBlock);
		}
		setFlag(QGraphicsItem::ItemIsMovable, true);
		setFlag(QGraphicsItem::ItemIsSelectable, true);
		setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
		this->setAcceptHoverEvents(true);
	}

	VGraphicsItemGroup::~VGraphicsItemGroup()
	{
		if (m_pVGraphicsItemGroupPrivate)
		{
			delete m_pVGraphicsItemGroupPrivate;
		}
	}

	QString VGraphicsItemGroup::DisplayName() const
	{
		return tr("group");
	}

	bool VGraphicsItemGroup::LoadFromXml(QXmlStreamReader* xml) 
	{
		return true;
	}

	bool VGraphicsItemGroup::SaveToXml(QXmlStreamWriter* xml)
	{
		xml->writeStartElement("group");
		xml->writeAttribute(tr("x"), QString("%1").arg(pos().x()));
		xml->writeAttribute(tr("y"), QString("%1").arg(pos().y()));
		xml->writeAttribute(tr("rotate"), QString("%1").arg(rotation()));

		foreach(QGraphicsItem * item, childItems()) 
		{
			removeFromGroup(item);
			VAbstractQGraphicsItem* ab = qgraphicsitem_cast<VAbstractQGraphicsItem*>(item);
			if (ab && !qgraphicsitem_cast<VGraphicsItemControlBlock*>(ab))
			{
				ab->UpdateCoordinate();
				ab->SaveToXml(xml);
			}
			addToGroup(item);
		}
		xml->writeEndElement();
		return true;
	}

	QGraphicsItem* VGraphicsItemGroup::Duplicate() const
	{
		VGraphicsItemGroup* item = 0;
		QList<QGraphicsItem*> copylist = DuplicateItems();
		item = CreateGroup(copylist);
		item->setPos(pos().x(), pos().y());
		item->SetPen(Pen());
		item->SetBrush(Brush());
		item->setTransform(transform());
		item->setTransformOriginPoint(transformOriginPoint());
		item->setRotation(rotation());
		item->setScale(scale());
		item->setZValue(zValue() + 0.1);
		item->UpdateCoordinate();
		item->m_width = m_width;
		item->m_height = m_height;
		return item;
	}

	void VGraphicsItemGroup::Control(int dir, const QPointF& delta)
	{
		QPointF local = mapFromParent(delta);
		if (dir < Left) return;
		if (dir == 9)
		{

		}
		Updatehandles();
	}

	void VGraphicsItemGroup::Stretch(int handle, double sx, double sy, const QPointF& origin)
	{
		QTransform trans;
		switch (handle)
		{
		case Right:
		case Left:
			sy = 1;
			break;
		case Top:
		case Bottom:
			sx = 1;
			break;
		default:
			break;
		}

		foreach(QGraphicsItem * item, childItems()) 
		{
			VAbstractQGraphicsItem* ab = qgraphicsitem_cast<VAbstractQGraphicsItem*>(item);
			if (ab && !qgraphicsitem_cast<VGraphicsItemControlBlock*>(ab))
			{
				ab->Stretch(handle, sx, sy, ab->mapFromParent(origin));
			}
		}

		trans.translate(origin.x(), origin.y());
		trans.scale(sx, sy);
		trans.translate(-origin.x(), -origin.y());

		prepareGeometryChange();
		m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect = trans.mapRect(m_pVGraphicsItemGroupPrivate->m_initialRect);
		m_width = m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect.width();
		m_height = m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect.height();
		Updatehandles();
	}

	void VGraphicsItemGroup::UpdateCoordinate()
	{
		QPointF pt1, pt2, delta;
		if (m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect.isNull())
			m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect = QGraphicsItemGroup::boundingRect();

		pt1 = mapToScene(transformOriginPoint());
		pt2 = mapToScene(m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect.center());
		delta = pt1 - pt2;
		m_pVGraphicsItemGroupPrivate->m_initialRect = m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect;
		m_width = m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect.width();
		m_height = m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect.height();
		setTransform(transform().translate(delta.x(), delta.y()));
		setTransformOriginPoint(m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect.center());
		moveBy(-delta.x(), -delta.y());
		foreach(QGraphicsItem * item, childItems()) 
		{
			VAbstractQGraphicsItem* ab = qgraphicsitem_cast<VAbstractQGraphicsItem*>(item);
			if (ab && !qgraphicsitem_cast<VGraphicsItemControlBlock*>(ab))
				ab->UpdateCoordinate();
		}
		Updatehandles();
	}

	QRectF VGraphicsItemGroup::boundingRect() const
	{
		return m_pVGraphicsItemGroupPrivate->m_itemsBoundingRect;
	}

	VGraphicsItemGroup* VGraphicsItemGroup::CreateGroup(const QList<QGraphicsItem*>& items) const
	{
		QList<QGraphicsItem*> ancestors;
		int n = 0;
		if (!items.isEmpty())
		{
			QGraphicsItem* parent = items.at(n++);
			while ((parent = parent->parentItem()))
				ancestors.append(parent);
		}
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
		VGraphicsItemGroup* pGroup = new VGraphicsItemGroup(commonAncestor);
		foreach(QGraphicsItem * item, items) {
			item->setSelected(false);
			QGraphicsItemGroup* g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
			if (!g)
				pGroup->addToGroup(item);
		}
		return pGroup;
	}

	QList<QGraphicsItem*> VGraphicsItemGroup::DuplicateItems() const
	{
		QList<QGraphicsItem*> copylist;
		foreach(QGraphicsItem * shape, childItems()) {
			VAbstractQGraphicsItem* ab = qgraphicsitem_cast<VAbstractQGraphicsItem*>(shape);
			if (ab && !qgraphicsitem_cast<VGraphicsItemControlBlock*>(ab))
			{
				QGraphicsItem* cp = ab->Duplicate();
				copylist.append(cp);
			}
		}
		return copylist;
	}

	void VGraphicsItemGroup::Updatehandles()
	{
		const QRectF& geom = this->boundingRect();
		const std::vector<VGraphicsItemControlBlock*>::iterator hend = m_vpControlBlock.end();
		for (std::vector<VGraphicsItemControlBlock*>::iterator it = m_vpControlBlock.begin(); it != hend; ++it)
		{
			VGraphicsItemControlBlock* pControlBlock = *it;;
			switch (pControlBlock->Dir())
			{
			case LeftTop:
				pControlBlock->Move(geom.x(), geom.y());
				break;
			case Top:
				pControlBlock->Move(geom.x() + geom.width() / 2, geom.y());
				break;
			case RightTop:
				pControlBlock->Move(geom.x() + geom.width(), geom.y());
				break;
			case Right:
				pControlBlock->Move(geom.x() + geom.width(), geom.y() + geom.height() / 2);
				break;
			case RightBottom:
				pControlBlock->Move(geom.x() + geom.width(), geom.y() + geom.height());
				break;
			case Bottom:
				pControlBlock->Move(geom.x() + geom.width() / 2, geom.y() + geom.height());
				break;
			case LeftBottom:
				pControlBlock->Move(geom.x(), geom.y() + geom.height());
				break;
			case Left:
				pControlBlock->Move(geom.x(), geom.y() + geom.height() / 2);
				break;
			case 9:
				pControlBlock->Move(transformOriginPoint().x(), transformOriginPoint().y());
				break;
			default:
				break;
			}
		}
	}

	QVariant VGraphicsItemGroup::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
	{
		if (change == QGraphicsItem::ItemSelectedHasChanged)
		{
			QGraphicsItemGroup* g = dynamic_cast<QGraphicsItemGroup*>(parentItem());
			if (!g)
				SetState(value.toBool() ? SelectionHandleActive : SelectionHandleOff);
			else
			{
				setSelected(false);
				return QVariant::fromValue<bool>(false);
			}
			if (value.toBool())
			{
				UpdateCoordinate();
			}
		}
		return QGraphicsItemGroup::itemChange(change, value);
	}

	void VGraphicsItemGroup::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		Q_UNUSED(widget);
		if (option->state & QStyle::State_Selected)
			qt_graphicsItem_highlightSelected(this, painter, option);
	}
}
