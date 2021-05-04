#include "LensListItem.h"

LensListItem::LensListItem(const int id, QString label)
{
	id_ = id;
	setText(label);
}

int LensListItem::getId()
{
	return id_;
}
