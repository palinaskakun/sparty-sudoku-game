/**
 * @file BonusResetter.cpp
 * @author Team Syceus
 */

#include "../pch.h"
#include "BonusResetter.h"
#include "../ItemCandy.h"

/**
 * Visitor for Candy object
 * @param candy
 */
void BonusResetter::VisitCandy(ItemCandy *candy)
{
    candy->SetIsEaten(false);
}
