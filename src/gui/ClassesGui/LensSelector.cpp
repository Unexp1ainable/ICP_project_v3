#include "LensSelector.h"

#include "LensSelectorItem.h"

LensSelector::LensSelector()
= default;


void LensSelector::add_lens(int id, QString label)
{
	auto item = new LensSelectorItem{ id, label };
	addItem(item);
}

void LensSelector::remove_lens(int index) const
{
	delete currentItem();
}

void LensSelector::edit_lens(QString label) const
{
	currentItem()->setText(label);
}

