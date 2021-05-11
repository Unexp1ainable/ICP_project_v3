/**
 * @file LensSelector.cpp
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Implementation of the LensSelector class
 */

#include "LensSelector.h"
#include "LensSelectorItem.h"

LensSelector::LensSelector()
= default;


void LensSelector::add_lens(int id, QString label)
{
	auto item = new LensSelectorItem{ id, label };
	addItem(item);
}

void LensSelector::remove_lens() const
{
	delete currentItem();
}

void LensSelector::edit_lens(QString label) const
{
	currentItem()->setText(label);
}

