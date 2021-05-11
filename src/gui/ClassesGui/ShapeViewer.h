#pragma once
/**
 * @file ShapeViewer.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief WIP canvas for showing shape of the ray on the surface
 */

#include <qpen.h>
#include <QWidget>

/**
 * @brief Wannabe canvas for showing shape of the ray cluster.
 */
class ShapeViewer : public QWidget
{
	Q_OBJECT

public:
	explicit ShapeViewer(QWidget* parent = nullptr);
	QPainter *painter;

	//QSize minimumSizeHint() const override;
	//QSize sizeHint() const override;
	//int heightForWidth(int) const override;
	//bool hasHeightForWidth() const override;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QPen pen;
	QBrush brush;
	bool antialiased;
	bool transformed;
	QPixmap pixmap;
};

