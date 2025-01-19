/**
 * @file SpartyFinder.h
 * @author Team Syceus
 *
 * Derived visitor class for sparty
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_SPARTYFINDER_H
#define PROJECT1_ACTIONSUDOKULIB_SPARTYFINDER_H

#include "ItemVisitor.h"
#include "../Sparty.h"

/**
 * Derived visitor class for sparty
 */
class SpartyFinder : public ItemVisitor
{
private:
    /// sparty init to null
    Sparty* mSparty = nullptr;

    /// xray init to null
    ItemXray* mXray = nullptr;

public:

    void VisitSparty(Sparty *sparty) override;

    void VisitXray(ItemXray *xray) override;

    /**
     * Getter for sparty
     * @return mSparty member variable
     */
    Sparty* GetSparty() const { return mSparty; }

    /**
     * Getter for xray
     * @return mXray member variable
     */
    ItemXray* GetXray() const { return mXray; }

};

#endif //PROJECT1_ACTIONSUDOKULIB_SPARTYFINDER_H
