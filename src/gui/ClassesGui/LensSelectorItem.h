#pragma once
#include <QListWidgetItem>

class LensSelectorItem : public QListWidgetItem
{
public:
	LensSelectorItem(int id, QString label);
	int getId();

private:
	int id_;
};

