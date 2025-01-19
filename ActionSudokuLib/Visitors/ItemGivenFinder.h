/**
 * @file ItemGivenFinder.h
 * @author Palina Skakun
 *
 * Derived visitor class for ItemDigit
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_VISITORS_ITEMGIVENFINDER_H
#define PROJECT1_ACTIONSUDOKULIB_VISITORS_ITEMGIVENFINDER_H

#include "ItemVisitor.h"
#include "../ItemGiven.h"

/**
 * Derived visitor class for ItemDigit
 */
class ItemGivenFinder : public ItemVisitor
{
private:
	/// ItemDigit init to null
	ItemGiven* mItemGiven = nullptr;

	/// xray init to null
	ItemXray* mXray = nullptr;

	/// Pointer to level loader object
	LevelLoader* mLevelLoader = nullptr;

public:

	void VisitGiven(ItemGiven *itemGiven) override;
	void VisitXray(ItemXray *xray) override;
	void VisitLevelLoader(LevelLoader *levelLoader) override;

	/**
	 * getter for ItemDigit
	 * @return ItemDigit member variable
	 */
	ItemGiven* GetItemGiven() const { return mItemGiven; }

	/**
	 * getter for xray
	 * @return mXray member variable
	 */
	ItemXray* GetXray() const { return mXray; }

};

#endif //PROJECT1_ACTIONSUDOKULIB_VISITORS_ITEMGIVENFINDER_H
