/**
 * @file OverlapChecker.cpp
 * @author Team Syceus
 */

#include "../pch.h"
#include "OverlapChecker.h"
#include "../ItemDigit.h"

/**
 * Constructor
 * @param x location x
 * @param y location y
 */
OverlapChecker::OverlapChecker(double x, double y)
{
    mX = x;
    mY = y;
}

/**
 * Visits a digit
 * @param digit digit we are visiting
 */
void OverlapChecker::VisitDigit(ItemDigit *digit)
{
    if (digit->HitTest(mX, mY))
    {
        mOverlaps = true;
    }
}