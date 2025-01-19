/**
 * @file ItemDigitFinder.cpp
 * @author audre
 * Class that finds digit objects
 */

#include "../pch.h"
#include "ItemDigitFinder.h"

using namespace std;

/**
 * Visits digit object
 * @param ItemDigit Object we are looking for
 */
void ItemDigitFinder::VisitDigit(ItemDigit *ItemDigit)
{
    mItemDigit = ItemDigit;
}

/**
 * Visits Xray object
 * @param xray Object we are looking for
 */
void ItemDigitFinder::VisitXray(ItemXray *xray)
{
    mXray = xray;
}

/**
 * Visits Level Loader object
 * @param levelLoader Object we are looking for
 */
void ItemDigitFinder::VisitLevelLoader(LevelLoader *levelLoader)
{
    mLevelLoader = levelLoader;
}




