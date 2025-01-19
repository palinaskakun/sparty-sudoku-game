/**
 * @file XrayFinder.h
 * @author Team Syceus
 *
 * Derived visitor class for container
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_XRAYFINDER_H
#define PROJECT1_ACTIONSUDOKULIB_XRAYFINDER_H

#include "ItemVisitor.h"

/**
 * Derived visitor class for container
 */
class XrayFinder : public ItemVisitor
{
private:
	///Pointer to xray object
    ItemXray* mXray = nullptr;

public:
	/**
	 *  Visitor for xray
	 * @param xray object that we're looking for
	 */
    void VisitXray(ItemXray *xray) override;

    /**
     * getter for container
     * @return mContainer member variable
     */
    ItemXray* GetXray() const { return mXray; }

};

#endif
