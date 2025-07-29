#pragma once
#include <QGraphicsScene>

namespace VisWindow
{
    enum VSceneAlignType
    {
        AlignType_Up,
        AlignType_Horz,
        AlignType_Vert,
        AlignType_Down,
        AlignType_Left,
        AlignType_Right,
        AlignType_Center,
        AlignType_Horzeven,
        AlignType_Verteven,
        AlignType_Width,
        AlignType_Height,
        AlignType_All,
    };

    class VSceneGrid
    {
    public:
        VSceneGrid(const QSize& grid = QSize(3200, 2400), const QSize& space = QSize(20, 20));
        void PaintGrid(QPainter* painter, const QRect& rect);

    protected:
        QSize m_sizeGrid;
        QSize m_sizeGridSpace;

    };

    class VGraphicsItemGroup;
	class VGraphicsScene : public QGraphicsScene
	{
		Q_OBJECT

	public:
        explicit VGraphicsScene(QObject* parent = 0);
        ~VGraphicsScene();
        void SetView(QGraphicsView* view);
        QGraphicsView* View();
        void Align(VSceneAlignType alignType);
        void MouseEvent(QGraphicsSceneMouseEvent* mouseEvent);
        VGraphicsItemGroup* CreateGroup(const QList<QGraphicsItem*>& items, bool isAdd = true);
        void DestroyGroup(QGraphicsItemGroup* group);

    signals:
        void Signals_itemMoved(QGraphicsItem* item, const QPointF& oldPosition);
        void Signals_itemRotate(QGraphicsItem* item, const qreal oldAngle);
        void Signals_itemAdded(QGraphicsItem* item);
        void Signals_itemResize(QGraphicsItem* item, int handle, const QPointF& scale);
        void Signals_itemControl(QGraphicsItem* item, int handle, const QPointF& newPos, const QPointF& lastPos_);

    protected:
        void drawBackground(QPainter* painter, const QRectF& rect) Q_DECL_OVERRIDE;
        void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvet) Q_DECL_OVERRIDE;
        void keyPressEvent(QKeyEvent* e) Q_DECL_OVERRIDE;
        void keyReleaseEvent(QKeyEvent* e) Q_DECL_OVERRIDE;

    private:
        qreal m_dx;
        qreal m_dy;
        bool  m_moved;
		VSceneGrid* m_pVSceneGrid;
        QGraphicsView* m_pQGraphicsView;

	};
}

