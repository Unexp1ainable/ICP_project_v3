#pragma once
#include <qlistwidget.h>

#include "rayTracer/Lens.h"

class LensList : public QListWidget
{
	Q_OBJECT

public:
	LensList();

	void add_lens(Lens lens);
	void remove_lens(int index);

public slots:
	void selection_changed();
};

