#pragma once
#include <qlistwidget.h>

class LensSelector : public QListWidget
{
	Q_OBJECT

public:
	LensSelector();

	/**
	 * @brief Adds new lens to the selector.
	 * 
	 * @param id Id of the lens from the engine
	 * @param label Label to be shown
	 */
	void add_lens(int id, QString label);
	/**
	 * @brief Edits already created lens.
	 * 
	 * @param label Label to be shown
	 */
	void edit_lens(QString label) const;
	/**
	 * @brief Removes currently selected lens.
	 */
	void remove_lens() const;

};

