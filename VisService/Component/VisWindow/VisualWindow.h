#pragma once

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QImage>
#include <QPainterPath>
#include <Memory>
#include "Graphics/VGraphicsItem.h"

namespace VisWindow
{
	class VisualWindowPrivate;
	class VisualWindow : public QWidget
	{
		Q_OBJECT

	public:
		VisualWindow(QWidget* parent = nullptr);
		~VisualWindow();
		void SetPen(const QPen& _pen);
		void SetBrush(const QBrush& _brush);
		void DispImage(const QImage& _img);
		void DispRect(const QRect& rect);
		void DispCircle(double Row, double Col, double Radius);
		void DispEllipse(double x, double y, double Phi, double w, double h);
		void DispPolygon(const QPolygon& polygon);
		void DispPainterPath(const QPainterPath& path);
		void ClearDisp();
		VGraphicsRectItem* DrawRect();
		VGraphicsEllipseItem* DrawEllipse();
		VGraphicsPolygonItem* DrawPolygon();

	private:
		VisualWindowPrivate* m_pVisualWindowPrivate;
	};
}
