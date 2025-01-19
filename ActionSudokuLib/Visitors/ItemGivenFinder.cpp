/**
 * @file ItemGivenFinder.cpp
 * @author Palina Skakun
 */

#include "../pch.h"
#include "ItemGivenFinder.h"

using namespace std;

/**
 * Visits object Given
 * @param ItemGiven Object we are looking for
 */
void ItemGivenFinder::VisitGiven(ItemGiven *ItemGiven)
{
	mItemGiven= ItemGiven;
}

/**
 * Visits object xray
 * @param xray Object we are looking for
 */
void ItemGivenFinder::VisitXray(ItemXray *xray)
{
	mXray = xray;
}

/**
 * Visits object LevelLoader
 * @param levelLoader Object we are looking for
 */
void ItemGivenFinder::VisitLevelLoader(LevelLoader *levelLoader)
{
	mLevelLoader = levelLoader;
}