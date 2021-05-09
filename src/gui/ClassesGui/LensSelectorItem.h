#pragma once
#include <QListWidgetItem>

/**
 * @brief Item for LensSelector.
 */
class LensSelectorItem : public QListWidgetItem
{
public:
	/**
	 * @brief Constructor.
	 * 
	 * @param id Id of the lens
	 * @param label Label to be shown
	 */
	LensSelectorItem(int id, QString label);

	/**
	 * @brief id_ getter.
	 * 
	 * @return Id
	 */
	int getId() const;

private:
	int id_;
};

