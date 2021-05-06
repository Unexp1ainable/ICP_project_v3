#pragma once
#include <qpen.h>
#include <QWidget>

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

