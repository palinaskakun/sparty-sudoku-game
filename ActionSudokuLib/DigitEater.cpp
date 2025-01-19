/**
 * @file DigitEater.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "DigitEater.h"
#include "ItemCandy.h"
#include "ItemDigit.h"
#include "ItemXray.h"
#include "Level.h"
#include "Scoreboard.h"

/**
 * updates member varibles x,y
 * @param x x value to change to
 * @param y y value to change to
 * @param full True when full
 */
DigitEater::DigitEater(double x, double y, bool full)
{
    mX = x;
    mY = y;
    mFull = full;
}

/**
 * Visitor for object Digit
 * @param digit Object we're looking for
 */
void DigitEater::VisitDigit(ItemDigit* digit)
{
    if (mAte)
    {
        return;
    }
    if (digit->HitTest(mX, mY))
    {
        if (mFull)
        {
            return;
        }
        mDigit = std::shared_ptr<ItemDigit>(digit);
        mAte = true;
    }
}

/**
 * Moves a digit from the playing area to the xray if Sparty isn't full.
 * @param xray Sparty's stomach
 */
void DigitEater::Eat(ItemXray *xray) //std::shared_ptr<Scoreboard> scoreboard)
{
    if (mDigit.get() != nullptr)
    {
        xray->Add(mDigit);
        mDigit->SetIsEaten(true);
    }

}

/**
 * Visitor for candy object
 * @param candy object we're looking for
 */
void DigitEater::VisitCandy(ItemCandy *candy)
{
    if (mAte)
    {
        return;
    }
    if (candy->HitTest(mX, mY))
    {
        if (mFull)
        {
            // draw message?
            return;
        }
        candy->SetIsEaten(true);
        mGotBonus = true;

    }
}
