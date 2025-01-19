/**
 * @file ItemCounter.h
 * @author Team Syceus
 *
 * Item counter class
 */

#ifndef PROJECT1__ITEMCOUNTER_H
#define PROJECT1__ITEMCOUNTER_H

#include "Visitors/ItemVisitor.h"

/**
 * Item counter class
 */
class ItemCounter : public ItemVisitor
{
private:
    ///Number of items in the game
    int mNumItems = 0;
    ///Number of spartys in the game
    int mNumSparty = 0;
    ///Number of givens in the game
    int mNumGivens = 0;
    ///Number of digits in the game
    int mNumDigits = 0;
    ///Number of xrays in the game
    int mNumXrays = 0;

public:
    /**
     * Visits an item in the game
     * @param item to be visited
     */
    void VisitItem(Item *item) override { mNumItems++; }

    /**
     * Visits a sparty in the game
     * @param sparty to be visited
     */
    void VisitSparty(Sparty *sparty) override { mNumSparty++; }

    /**
     * Visits a given in the game
     * @param given to be visited
     */
    void VisitGiven(ItemGiven *given) override { mNumGivens++; }

    /**
     * Visits a digit in the game
     * @param digit to be visited
     */
    void VisitDigit(ItemDigit *digit) override { mNumDigits++; }

    /**
     * Visits a xray in the game
     * @param xray to be visited
     */
    void VisitXray(ItemXray *xray) override { mNumXrays++; }

    /**
     * Gets the number of items in the game
     * @return mNumItems member variable
     */
    int GetItemCount() const { return mNumItems; }

    /**
     * Gets the number of sparty in the game
     * @return mNumSarty member variable
     */
    int GetSpartyCount() const { return mNumSparty; }

    /**
     * Gets the number of givens in the game
     * @return mNumGivens member variable
     */
    int GetGivenCount() const { return mNumGivens; }

    /**
     * Gets the number of digits in the game
     * @return mNumDigits member variable
     */
    int GetDigitCount() const { return mNumDigits; }

    /**
     * Gets the number of xrays in the game
     * @return mNumXrays member variable
     */
    int GetXrayCount() const { return mNumXrays; }

};

#endif //PROJECT1__ITEMCOUNTER_H
