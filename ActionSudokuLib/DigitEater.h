/**
 * @file DigitEater.h
 * @author Team Syceus
 *
 * derived visitor class for digts eaten
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_DIGITEATER_H
#define PROJECT1_ACTIONSUDOKULIB_DIGITEATER_H

#include "Visitors/ItemVisitor.h"

class Scoreboard;
/**
 * derived visitor class for digts eaten
 */
class DigitEater : public ItemVisitor
{
private:
    ///digit state if eaten
    bool mAte = false;
    /// digit x coordinate
    double mX;
    /// digit y coordinate
    double mY;
    /// pointer to the digit
    std::shared_ptr<ItemDigit> mDigit = nullptr;

    /// pointer to the digit
    std::shared_ptr<ItemCandy> mCandy;

    /// if capacity reached for xray
    bool mFull = false;

    /// if candy was eaten and bonus gotten
    bool mGotBonus = false;

public:

    DigitEater(double x, double y, bool full);
    void VisitDigit(ItemDigit *digit) override;

    void VisitCandy(ItemCandy *candy) override;

    void Eat(ItemXray *xray);//, std::shared_ptr<Scoreboard> scoreboard);

    /**
     * getter for bonus
     * @return mGotBonus bool member variable
     */
    bool GotBonus() { return mGotBonus; }

    /**
     * getter for full
     * @return mFull bool member variable
     */
    bool GetFull() { return mFull; }

    /**
     * getter for digit
     * @return mDigit member variable
     */
    std::shared_ptr<ItemDigit> GetDigit() { return mDigit; }

    /**
     * getter for x val
     * @return mX member variable
     */
    double GetX() { return mX; }

    /**
     * getter for y val
     * @return mY member variable
     */
    double GetY() { return mY; }
};

#endif //PROJECT1_ACTIONSUDOKULIB_DIGITEATER_H
