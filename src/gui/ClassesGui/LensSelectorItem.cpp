#include "LensSelectorItem.h"

LensSelectorItem::LensSelectorItem(const int id, QString label)
{
	id_ = id;
	setText(label);
}

int LensSelectorItem::getId() const
{
	return id_;
}
