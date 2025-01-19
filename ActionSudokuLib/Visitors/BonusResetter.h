/**
 * @file BonusResetter.h
 * @author Team Syceus
 *
 * Class derived from Item Visitor that visits Candy object
 */

#include "ItemVisitor.h"

#ifndef PROJECT1_ACTIONSUDOKULIB_VISITORS_BONUSRESETTER_H
#define PROJECT1_ACTIONSUDOKULIB_VISITORS_BONUSRESETTER_H

/**
 * Class derived from Item Visitor that visits Candy object
 */
class BonusResetter : public ItemVisitor
{
private:

public:
    void VisitCandy(ItemCandy *candy) override;

};

#endif //PROJECT1_ACTIONSUDOKULIB_VISITORS_BONUSRESETTER_H
