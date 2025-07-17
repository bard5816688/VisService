#pragma once
#include <QGraphicsItem>
#include <QXmlStreamReader>
#include <QBrush>
#include <QPen>
#include <QColor>
#include "VGraphicsItemControlBlock.h"

namespace VisWindow
{
	template <typename BaseType = QGraphicsItem>
    class VAbstractGraphicsItem : public BaseType
    {
    public:
        explicit VAbstractGraphicsItem(QGraphicsItem* parent = 0)
            :BaseType(parent)
        {
            m_width = m_height = 0;
        }
        virtual ~VAbstractGraphicsItem() {
        }
		virtual QString DisplayName() const 
        {
			return QString("AbstractType");
		}
        virtual void Control(int dir, const QPointF& delta) 
        {
            Q_UNUSED(dir); Q_UNUSED(delta);
        }
        virtual void Stretch(int, double, double, const QPointF&) 
        {
        }
        virtual QRectF Rect() const 
        {
            return m_localRect;
        }
        virtual void UpdateCoordinate() 
        {
        }
        virtual void Move(const QPointF& point) 
        {
            Q_UNUSED(point);
        }
        virtual QGraphicsItem* Duplicate() const 
        {
            return NULL;
        }
        virtual int HandleCount() const 
        {
            return (int)m_vpControlBlock.size();
        }
        virtual bool LoadFromXml(QXmlStreamReader* xml) = 0;
        virtual bool SaveToXml(QXmlStreamWriter* xml) = 0;
        int CollidesWithHandle(const QPointF& point) const
        {
            const std::vector<VGraphicsItemControlBlock*>::const_reverse_iterator hend = m_vpControlBlock.rend();
            for (std::vector<VGraphicsItemControlBlock*>::const_reverse_iterator it = m_vpControlBlock.rbegin(); it != hend; ++it)
            {
                QPointF pt = (*it)->mapFromScene(point);
                if ((*it)->contains(pt))
                {
                    return (*it)->Dir();
                }
            }
            return Handle_None;
        }
        virtual QPointF HandlePos(int handle) const
        {
            const std::vector<VGraphicsItemControlBlock*>::const_reverse_iterator hend = m_vpControlBlock.rend();
            for (std::vector<VGraphicsItemControlBlock*>::const_reverse_iterator it = m_vpControlBlock.rbegin(); it != hend; ++it)
            {
                if ((*it)->Dir() == handle)
                {
                    return (*it)->pos();
                }
            }
            return QPointF();
        }
        int SwapHandle(int handle, const QPointF& scale) const
        {
            int dir = Handle_None;
            if (scale.x() < 0 || scale.y() < 0)
            {
                switch (handle)
                {
                case RightTop:
                    if (scale.x() < 0 && scale.y() < 0)
                        dir = LeftBottom;
                    else if (scale.x() > 0 && scale.y() < 0)
                        dir = RightBottom;
                    else
                        dir = LeftTop;
                    break;
                case RightBottom:
                    if (scale.x() < 0 && scale.y() < 0)
                        dir = LeftTop;
                    else if (scale.x() > 0 && scale.y() < 0)
                        dir = RightTop;
                    else
                        dir = LeftBottom;
                    break;
                case LeftBottom:
                    if (scale.x() < 0 && scale.y() < 0)
                        dir = RightTop;
                    else if (scale.x() > 0 && scale.y() < 0)
                        dir = LeftTop;
                    else
                        dir = RightBottom;
                    break;
                case LeftTop:
                    if (scale.x() < 0 && scale.y() < 0)
                        dir = RightBottom;
                    else if (scale.x() > 0 && scale.y() < 0)
                        dir = LeftBottom;
                    else
                        dir = RightTop;
                    break;
                case Right:
                    if (scale.x() < 0)
                        dir = Left;
                    break;
                case Left:
                    if (scale.x() < 0)
                        dir = Right;
                    break;
                case Top:
                    if (scale.y() < 0)
                        dir = Bottom;
                    break;
                case Bottom:
                    if (scale.y() < 0)
                        dir = Top;
                    break;
                }
            }
            return dir;
        }
        virtual QPointF Opposite(int handle) 
        {
            QPointF pt;
            switch (handle)
            {
            case Right:
                pt = m_vpControlBlock.at(Left - 1)->pos();
                break;
            case RightTop:
                pt = m_vpControlBlock[LeftBottom - 1]->pos();
                break;
            case RightBottom:
                pt = m_vpControlBlock[LeftTop - 1]->pos();
                break;
            case LeftBottom:
                pt = m_vpControlBlock[RightTop - 1]->pos();
                break;
            case Bottom:
                pt = m_vpControlBlock[Top - 1]->pos();
                break;
            case LeftTop:
                pt = m_vpControlBlock[RightBottom - 1]->pos();
                break;
            case Left:
                pt = m_vpControlBlock[Right - 1]->pos();
                break;
            case Top:
                pt = m_vpControlBlock[Bottom - 1]->pos();
                break;
            }
            return pt;
        }

        QColor BrushColor() const 
        {
            return m_brush.color();
        }
        QBrush Brush() const 
        {
            return m_brush;
        }
        QPen Pen() const 
        {
            return m_pen;
        }
        QColor PenColor() const 
        {
            return m_pen.color();
        }
        void SetPen(const QPen& pen) 
        {
            m_pen = pen;
        }
        void SetBrush(const QBrush& brush) 
        {
            m_brush = brush;
        }
        void SetBrushColor(const QColor& color) 
        {
            m_brush.setColor(color);
        }
        qreal  Width() const 
        {
            return m_width;
        }
        void SetWidth(qreal width)
        {
            m_width = width;
            UpdateCoordinate();
        }
        qreal Height() const 
        {
            return m_height;
        }
        void SetHeight(qreal height)
        {
            m_height = height;
            UpdateCoordinate();
        }

    protected:
        virtual void Updatehandles()
        {
        }
        void SetState(SelectionHandleState st)
        {
            const std::vector<VGraphicsItemControlBlock*>::iterator hend = m_vpControlBlock.end();
            for (std::vector<VGraphicsItemControlBlock*>::iterator it = m_vpControlBlock.begin(); it != hend; ++it)
            {
                (*it)->SetState(st);
            }
        }

protected:
        QBrush m_brush;
        QPen   m_pen;
		std::vector<VGraphicsItemControlBlock*> m_vpControlBlock;
        QRectF m_localRect;
        qreal m_width;
        qreal m_height;
    };

    enum eVGraphicsItemType
    {
        eVGraphicsItemType_Base = QGraphicsItem::UserType + 1,
        eVGraphicsItemType_Rect,
        eVGraphicsItemType_Ellipse,
        eVGraphicsItemType_Polygon,
        eVGraphicsItemType_Line,
        eVGraphicsItemType_Bezier,
    };

	class VGraphicsItem : public QObject, public VAbstractGraphicsItem<QGraphicsItem>
	{
		Q_OBJECT
		Q_PROPERTY(QColor Pen READ PenColor WRITE SetPen)
		Q_PROPERTY(QColor Brush READ BrushColor WRITE SetBrushColor)
		Q_PROPERTY(qreal  Width READ Width WRITE SetWidth)
		Q_PROPERTY(qreal  Height READ Height WRITE SetHeight)
        Q_PROPERTY(QPointF  position READ pos WRITE setPos)

	public:
		VGraphicsItem(QGraphicsItem* parent = nullptr, bool _bEnableHandles = true);
        virtual int type() const Q_DECL_OVERRIDE;
        virtual bool LoadFromXml(QXmlStreamReader* xml) override;
        virtual bool SaveToXml(QXmlStreamWriter* xml) override;

	signals:
		void Signals_SelectedChange(QGraphicsItem* item);
		void Signals_PoseChange(QGraphicsItem* item);

	protected:
        virtual void Updatehandles() override;
        virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value) Q_DECL_OVERRIDE;
		virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) Q_DECL_OVERRIDE;

	};

    class VGraphicsRectItemPrivate;
	class VGraphicsRectItem : public VGraphicsItem
	{
    public:
        VGraphicsRectItem(const QRect& rect, bool isRound = false, QGraphicsItem* parent = 0);
        ~VGraphicsRectItem();
        QPainterPath shape() const Q_DECL_OVERRIDE;
        virtual int type() const Q_DECL_OVERRIDE;
        virtual void Control(int dir, const QPointF& delta);
        virtual void Stretch(int handle, double sx, double sy, const QPointF& origin);
        virtual QRectF Rect() const;
        virtual void UpdateCoordinate();
        virtual void Move(const QPointF& point);
        virtual QGraphicsItem* Duplicate() const override;
        virtual QString DisplayName() const override;
        virtual bool LoadFromXml(QXmlStreamReader* xml) override;
        virtual bool SaveToXml(QXmlStreamWriter* xml) override;
        virtual QRectF boundingRect() const Q_DECL_OVERRIDE;

    protected:
        virtual void Updatehandles() override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;

    private:
        VGraphicsRectItemPrivate* m_pVGraphicsRectItemPrivate = nullptr;
	};

    class VGraphicsEllipseItemPrivate;
	class VGraphicsEllipseItem : public VGraphicsRectItem
    {
    public:
        VGraphicsEllipseItem(const QRect& rect, QGraphicsItem* parent = 0);
        ~VGraphicsEllipseItem();
        QPainterPath shape() const Q_DECL_OVERRIDE;
        virtual int type() const Q_DECL_OVERRIDE;
        virtual void Control(int dir, const QPointF& delta) override;
        virtual QGraphicsItem* Duplicate() const override;
        virtual QString DisplayName() const override;
        virtual bool LoadFromXml(QXmlStreamReader* xml) override;
        virtual bool SaveToXml(QXmlStreamWriter* xml) override;
        virtual QRectF boundingRect() const Q_DECL_OVERRIDE;

    protected:
        virtual void Updatehandles() override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;

    private:
        VGraphicsEllipseItemPrivate* m_pVGraphicsEllipseItemPrivate = nullptr;

    };

    class VGraphicsPolygonItem : public VGraphicsItem
    {
    public:
        VGraphicsPolygonItem(QGraphicsItem* parent = 0);
        QPainterPath shape() const Q_DECL_OVERRIDE;
        QPolygonF Polygon() const;
        virtual int type() const Q_DECL_OVERRIDE;
        virtual void AddPoint(const QPointF& point);
        virtual void EndPoint(const QPointF& point);
        virtual void Control(int dir, const QPointF& delta) override;
        virtual void Stretch(int handle, double sx, double sy, const QPointF& origin) override;
        virtual void UpdateCoordinate() override;
        virtual bool LoadFromXml(QXmlStreamReader* xml) override;
        virtual bool SaveToXml(QXmlStreamWriter* xml) override;
        virtual QString DisplayName() const override;
        virtual QGraphicsItem* Duplicate() const override;
        virtual QRectF boundingRect() const Q_DECL_OVERRIDE;

    protected:
        virtual void Updatehandles()override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;
        QPolygonF m_points;
        QPolygonF m_initialPoints;

    };

    class VGraphicsLineItem : public VGraphicsPolygonItem
    {
    public:
        VGraphicsLineItem(QGraphicsItem* parent = 0);
        QPainterPath shape() const Q_DECL_OVERRIDE;
        virtual int type() const Q_DECL_OVERRIDE;
        virtual QGraphicsItem* Duplicate() const override;
        virtual void AddPoint(const QPointF& point) override;
        virtual void EndPoint(const QPointF& point) override;
        virtual QPointF Opposite(int handle) override;
        virtual void UpdateCoordinate() override;
        virtual int HandleCount() const override;
        virtual void Stretch(int handle, double sx, double sy, const QPointF& origin) override;
        virtual bool LoadFromXml(QXmlStreamReader* xml) override;
        virtual bool SaveToXml(QXmlStreamWriter* xml) override;
        virtual QString DisplayName() const override;
    protected:
        virtual void Updatehandles()override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;

    };

    class VGraphicsBezierItem : public VGraphicsPolygonItem
    {
    public:
        VGraphicsBezierItem(bool bbezier = true, QGraphicsItem* parent = 0);
        QPainterPath shape() const Q_DECL_OVERRIDE;
        virtual int type() const Q_DECL_OVERRIDE;
        virtual QGraphicsItem* Duplicate() const override;
        virtual bool LoadFromXml(QXmlStreamReader* xml) override;
        virtual bool SaveToXml(QXmlStreamWriter* xml) override;
        virtual QString DisplayName() const override;
    protected:
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;
    private:
        bool m_isBezier;
    };

    typedef VAbstractGraphicsItem<QGraphicsItem> VAbstractQGraphicsItem;
    class VGraphicsItemGroupPrivate;
	class VGraphicsItemGroup : public QObject, public VAbstractGraphicsItem <QGraphicsItemGroup>
    {
        Q_OBJECT
            Q_PROPERTY(QColor Pen READ PenColor WRITE SetPen)
            Q_PROPERTY(QColor Brush READ BrushColor WRITE SetBrushColor)
            Q_PROPERTY(qreal  Width READ Width WRITE SetWidth)
            Q_PROPERTY(qreal  Height READ Height WRITE SetHeight)
            Q_PROPERTY(QPointF  position READ pos WRITE setPos)

    public:
        explicit VGraphicsItemGroup(QGraphicsItem* parent = 0);
        ~VGraphicsItemGroup();
        QString DisplayName() const;
        virtual bool LoadFromXml(QXmlStreamReader* xml) override;
        virtual bool SaveToXml(QXmlStreamWriter* xml) override;
        virtual QGraphicsItem* Duplicate() const override;
        virtual void Control(int dir, const QPointF& delta) override;
        virtual void Stretch(int handle, double sx, double sy, const QPointF& origin) override;
        virtual void UpdateCoordinate() override;
        virtual QRectF boundingRect() const Q_DECL_OVERRIDE;

    signals:
        void Signals_selectedChange(QGraphicsItem* item);

    protected:
        VGraphicsItemGroup* CreateGroup(const QList<QGraphicsItem*>& items) const;
        QList<QGraphicsItem*> DuplicateItems() const ;
        virtual void Updatehandles() override;
        virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value) Q_DECL_OVERRIDE;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) Q_DECL_OVERRIDE;

    private:
        VGraphicsItemGroupPrivate* m_pVGraphicsItemGroupPrivate = nullptr;
    };
}

