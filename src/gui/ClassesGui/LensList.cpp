#include "LensList.h"

#include "LensListItem.h"

LensList::LensList()
= default;


void LensList::add_lens(int id, QString label)
{
	auto item = new LensListItem{ id, label };
	addItem(item);
}

void LensList::remove_lens(int index)
{
	delete currentItem();
}

void LensList::edit_lens(QString label)
{
	currentItem()->setText(label);
}

