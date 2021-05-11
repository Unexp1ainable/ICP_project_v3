/**
 * @file LensSelectorItem.cpp
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Implementation of the LensSelectorItem class
 */

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
