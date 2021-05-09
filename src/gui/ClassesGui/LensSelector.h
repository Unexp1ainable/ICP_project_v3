#pragma once
#include <qlistwidget.h>

#include "rayTracer/Lens.h"

class LensSelector : public QListWidget
{
	Q_OBJECT

public:
	LensSelector();

	void add_lens(int id, QString label);
	void edit_lens(QString label) const;
	void remove_lens(int index) const;

};

