#pragma once
#include <QListWidgetItem>

class LensSelectorItem : public QListWidgetItem
{
public:
	LensSelectorItem(int id, QString label);
	int getId() const;

private:
	int id_;
};

