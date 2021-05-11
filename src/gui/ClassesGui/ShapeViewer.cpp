/**
 * @file ShapeViewer.cpp
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Implementation of the ShapeViewer class
 */

#include "ShapeViewer.h"

#include <qpainter.h>
#include <qpainterpath.h>

ShapeViewer::ShapeViewer(QWidget* parent)
	: QWidget(parent)
{
	antialiased = false;
	transformed = false;

	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);

}


void ShapeViewer::paintEvent(QPaintEvent* /* event */)
{
	static const QPoint points[4] = {
		QPoint(10, 80),
		QPoint(20, 10),
		QPoint(80, 30),
		QPoint(90, 70)
	};

	QRect rect(10, 20, 80, 60);

	QPainterPath path;
	path.moveTo(20, 80);
	path.lineTo(20, 30);
	path.cubicTo(80, 0, 50, 50, 80, 80);

	QPainter painter(this);

	painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}