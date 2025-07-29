#include "VGraphicsItemControlBlock.h"
#include <QPainter>

namespace VisWindow
{
	class VGraphicsItemControlBlockPrivate
	{
	public:
		VGraphicsItemControlBlockPrivate(int d, bool control)
			: m_dir(d)
			, m_controlPoint(control)
			, m_state(SelectionHandleOff)
			, m_borderColor("white")
		{
		}
		~VGraphicsItemControlBlockPrivate()
		{
		}
		const int m_dir;
		bool   m_controlPoint;
		SelectionHandleState m_state;
		QColor m_borderColor;
	};

	VGraphicsItemControlBlock::VGraphicsItemControlBlock(QGraphicsItem* parent, int d, bool control)
		:QGraphicsRectItem(-SELECTION_HANDLE_SIZE / 2,
						   -SELECTION_HANDLE_SIZE / 2,
						   SELECTION_HANDLE_SIZE,
						   SELECTION_HANDLE_SIZE, parent)
	{
		m_pVGraphicsItemControlBlockPrivate = new VGraphicsItemControlBlockPrivate(d, control);
	}

	VGraphicsItemControlBlock::~VGraphicsItemControlBlock()
	{
		if (m_pVGraphicsItemControlBlockPrivate)
		{
			delete m_pVGraphicsItemControlBlockPrivate;
		}
	}

	int VGraphicsItemControlBlock::Dir() const
	{
		return m_pVGraphicsItemControlBlockPrivate->m_dir;
	}

	void VGraphicsItemControlBlock::SetState(SelectionHandleState st)
	{
		if (st == m_pVGraphicsItemControlBlockPrivate->m_state)
			return;
		switch (st)
		{
		case SelectionHandleOff:
			hide();
			break;
		case SelectionHandleInactive:
		case SelectionHandleActive:
			show();
			break;
		}
		m_pVGraphicsItemControlBlockPrivate->m_borderColor = Qt::white;
		m_pVGraphicsItemControlBlockPrivate->m_state = st;
	}

	void VGraphicsItemControlBlock::Move(qreal x, qreal y)
	{
		setPos(x, y);
	}

	void VGraphicsItemControlBlock::HoverEnterEvent(QGraphicsSceneHoverEvent* e)
	{
		m_pVGraphicsItemControlBlockPrivate->m_borderColor = Qt::blue;
		update();
		QGraphicsRectItem::hoverEnterEvent(e);
	}

	void VGraphicsItemControlBlock::HoverLeaveEvent(QGraphicsSceneHoverEvent* e)
	{
		m_pVGraphicsItemControlBlockPrivate->m_borderColor = Qt::white;
		update();
		QGraphicsRectItem::hoverLeaveEvent(e);
	}

	void VGraphicsItemControlBlock::Paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		painter->save();
		painter->setPen(Qt::SolidLine);
		painter->setBrush(QBrush(m_pVGraphicsItemControlBlockPrivate->m_borderColor));

		painter->setRenderHint(QPainter::Antialiasing, false);

		if (m_pVGraphicsItemControlBlockPrivate->m_controlPoint)
		{
			painter->setPen(QPen(Qt::red, Qt::SolidLine));
			painter->setBrush(Qt::green);
			painter->drawEllipse(rect().center(), 3, 3);
		}
		else
			painter->drawRect(rect());
		painter->restore();
	}
}
