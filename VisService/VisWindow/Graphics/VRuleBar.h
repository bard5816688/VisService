#pragma once
#include <QWidget>
#include <QGraphicsView>

#define VRULER_SIZE    16

namespace VisWindow
{
    class VCornerBox : public QWidget
    {
        Q_OBJECT
    public:
        explicit VCornerBox(QWidget* parent);

    protected:
        virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

    };

	class VRuleBar : public QWidget
	{
        Q_OBJECT
    public:
        explicit VRuleBar(Qt::Orientation direction, QGraphicsView* view, QWidget* parent = 0);
        void SetRange(double lower, double upper, double max_size);
        void UpdatePosition(const QPoint& pos) ;

    protected:
        virtual void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

    private:
        void DrawTicker(QPainter* painter);
        void DrawPos(QPainter* painter);
        Qt::Orientation m_direction;
        QPoint m_lastPos;
        QColor m_faceColor;
		QGraphicsView* m_view;
        double m_lower;
        double m_upper;
        double m_maxsize;

	};
}


