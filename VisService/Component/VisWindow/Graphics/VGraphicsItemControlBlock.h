#pragma once
#include <QGraphicsRectItem>

class QGraphicsItem;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;

namespace VisWindow
{
    enum
    {
        SELECTION_HANDLE_SIZE = 6, SELECTION_MARGIN = 10
    };

    enum SelectionHandleState
    {
        SelectionHandleOff, SelectionHandleInactive, SelectionHandleActive
    };

    enum
    {
        Handle_None = 0, LeftTop, Top, RightTop, Right, RightBottom, Bottom, LeftBottom, Left
    };

    class VGraphicsItemControlBlockPrivate;
	class VGraphicsItemControlBlock :public QGraphicsRectItem
	{
    public:

        VGraphicsItemControlBlock(QGraphicsItem* parent, int d, bool control = false);
        ~VGraphicsItemControlBlock();
        int Dir() const;
        void SetState(SelectionHandleState st);
        void Move(qreal x, qreal y);

    protected:
        void HoverEnterEvent(QGraphicsSceneHoverEvent* e);
        void HoverLeaveEvent(QGraphicsSceneHoverEvent* e);
        void Paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    private:
        VGraphicsItemControlBlockPrivate* m_pVGraphicsItemControlBlockPrivate = nullptr;
	};
}


