#pragma once
#include <QListWidgetItem>

class LensListItem : public QListWidgetItem
{
public:
	LensListItem(int id, QString label);
	int getId();

private:
	int id_;
};

