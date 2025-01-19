/**
 * @file OverlapChecker.h
 * @author Team Syceus
 *
 *
 */

#include "ItemVisitor.h"

#ifndef PROJECT1_ACTIONSUDOKULIB_VISITORS_OVERLAPCHECKER_H
#define PROJECT1_ACTIONSUDOKULIB_VISITORS_OVERLAPCHECKER_H

/**
 * Derived visitor class that checks for overlapping digits
 */
class OverlapChecker : public ItemVisitor
{
private:
    /// True if an overlap is found
    bool mOverlaps = false;

    /// x coordinate to check for overlaps
    double mX;
    /// y coordinate to check for overlaps
    double mY;

public:

    OverlapChecker(double x, double y);

    void VisitDigit(ItemDigit *digit) override;

    /**
     * Checks if an overlapping digit was found
     * @return true if an overlap was found
     */
    bool Overlaps() { return mOverlaps; }

};

#endif //PROJECT1_ACTIONSUDOKULIB_VISITORS_OVERLAPCHECKER_H
