#pragma once
#include <qlistwidget.h>

#include "rayTracer/Lens.h"

class LensList : public QListWidget
{
	Q_OBJECT

public:
	LensList();

	void add_lens(int id, QString label);
	void edit_lens(QString label);
	void remove_lens(int index);

};

