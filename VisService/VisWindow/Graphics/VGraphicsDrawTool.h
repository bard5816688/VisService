#pragma once
#include <QList>
#include <QPen>

class QGraphicsSceneMouseEvent;
class QGraphicsPathItem;

namespace VisWindow
{
    class VGraphicsItem;
    class VGraphicsItemGroup;
    class VGraphicsPolygonItem;
    class VGraphicsScene;

    enum VGraphicsDrawShape
    {
        DrawShape_Selection,
        DrawShape_Line,
        DrawShape_Rectangle,
        DrawShape_Roundrect,
        DrawShape_Ellipse,
        DrawShape_Bezier,
        DrawShape_Polygon,
        DrawShape_Polyline,
    };

    class VGraphicsDrawTool
    {
    public:
        VGraphicsDrawTool(VGraphicsDrawShape shape);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene);
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene);
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene);
        virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene);
        static VGraphicsDrawTool* FindTool(VGraphicsDrawShape drawShape);
        static VGraphicsDrawShape c_drawShape;
        static QPen c_pen;
        static QBrush c_brush;

    protected:
        VGraphicsDrawShape m_drawShape;
        bool m_hoverSizer;
        static QList<VGraphicsDrawTool*> c_tools;
        static QPointF c_down;
        static quint32 c_nDownFlags;
        static QPointF c_last;

    };

    class VGraphicsSelectTool : public VGraphicsDrawTool
    {
    public:
        VGraphicsSelectTool();
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;

    private:
        QPointF initialPositions;
        QPointF opposite_;
        QGraphicsPathItem* dashRect = nullptr;
        VGraphicsItemGroup* selLayer = nullptr;

    };

    class VGraphicsRectTool : public VGraphicsDrawTool
    {
    public:
        VGraphicsRectTool(VGraphicsDrawShape drawShape);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;

    private:
		VGraphicsItem* item = nullptr;

    };

    class VGraphicsPolygonTool : public VGraphicsDrawTool
    {
    public:
        VGraphicsPolygonTool(VGraphicsDrawShape shape);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event, VGraphicsScene* scene) override;

    private:
        VGraphicsPolygonItem* item = nullptr;
        int m_nPoints;                                        
        QPointF initialPositions;

    };
}

