/**
 * @file ItemDigitFinder.h
 * @author Team Syceus
 *
 * Derived visitor class for ItemDigit
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_ITEMDIGITFINDER_H
#define PROJECT1_ACTIONSUDOKULIB_ITEMDIGITFINDER_H

#include "ItemVisitor.h"
#include "../ItemDigit.h"

/**
 * Derived visitor class for ItemDigit
 */
class ItemDigitFinder : public ItemVisitor
{
private:
    /// ItemDigit init to null
    ItemDigit* mItemDigit = nullptr;

    /// xray init to null
    ItemXray* mXray = nullptr;

	///Level loader pointer
    LevelLoader* mLevelLoader = nullptr;

public:

    void VisitDigit(ItemDigit *itemDigit) override;
    void VisitXray(ItemXray *xray) override;
    void VisitLevelLoader(LevelLoader *levelLoader) override;

    /**
     * getter for ItemDigit
     * @return ItemDigit member variable
     */
    ItemDigit* GetItemDigit() const { return mItemDigit; }

    /**
     * getter for xray
     * @return mXray member variable
     */
    ItemXray* GetXray() const { return mXray; }

};

#endif //PROJECT1_ACTIONSUDOKULIB_ITEMDIGITFINDER_H
