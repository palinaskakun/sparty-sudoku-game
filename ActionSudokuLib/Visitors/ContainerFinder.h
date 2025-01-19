/**
 * @file ContainerFinder.h
 * @author Team Syceus
 *
 * Derived visitor class for container
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_CONTAINERFINDER_H
#define PROJECT1_ACTIONSUDOKULIB_CONTAINERFINDER_H

#include "ItemVisitor.h"
#include "../Container.h"

/**
 * Derived visitor class for container
 */
class ContainerFinder : public ItemVisitor
{
private:
    /// container init to null
    Container* mContainer = nullptr;

    /// xray init to null
    ItemXray* mXray = nullptr;

public:

    void VisitContainer(Container *container) override;
    void VisitXray(ItemXray *xray) override;

    /**
     * getter for container
     * @return mContainer member variable
     */
    Container* GetContainer() const { return mContainer; }

    /**
     * getter for xray
     * @return mXray member variable
     */
    ItemXray* GetXray() const { return mXray; }

};

#endif //PROJECT1_ACTIONSUDOKULIB_CONTAINERFINDER_H
