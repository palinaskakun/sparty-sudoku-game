/**
 * @file ItemVisitor.h
 * @author Team Syceus
 *
 * A visitor class for Item
 */

#ifndef PROJECT1__ITEMVISITOR_H
#define PROJECT1__ITEMVISITOR_H

class Item;
class Sparty;
class ItemXray;
class ItemDigit;
class ItemCandy;
class ItemGiven;
class Container;
class LevelLoader;

/**
 * A visitor class for Item
 */
class ItemVisitor
{
private:
    /// xray init to null
    ItemXray* mVisXray = nullptr;

    /// mitems init empty
    std::vector<std::shared_ptr<Item>> mVisItems;

public:
    /**
     * Visit function for each item
     * @param item Object we're looking for
     */
    virtual void VisitItem(Item *item) {}

    /**
     * Visit function for each given
     * @param given Object we're looking for
     */
    virtual void VisitGiven(ItemGiven *given) {}

    /**
     * Visit function for each digit
     * @param digit Object we're looking for
     */
    virtual void VisitDigit(ItemDigit *digit) {}

    /**
     * Visit function for each candy
     * @param candy Object we're looking for
     */
    virtual void VisitCandy(ItemCandy *candy) {}

    /**
     * Visit function for each xray
     * @param xray Object we're looking for
     */
    virtual void VisitXray(ItemXray *xray) {}

    /**
     * Visit function for each sparty
     * @param sparty Object we're looking for
     */
    virtual void VisitSparty(Sparty *sparty) {}

    /**
     * Visit function for each container
     * @param container Object we're looking for
     */
    virtual void VisitContainer(Container *container) {}

    /**
     * Visit function for levelloader
     * @param levelLoader Object we're looking for
     */
    virtual void VisitLevelLoader(LevelLoader *levelLoader) {}

    /**
     * getter for xray
     * @return mXray member variable
     */
    ItemXray* GetXray() const { return mVisXray; }

    /**
     * getter for mItems in level
     * @return mItems member variable
     */
    std::vector<std::shared_ptr<Item>> GetItems() const { return mVisItems ;}

    /**
     * Sets visitor items
     * @param items Value we're setting to
     */
    void SetItems(std::vector<std::shared_ptr<Item>> items) { mVisItems = items;}

    /**
     * Sets visitor item
     * @param xray Value we're stting to
     */
    void SetXray(ItemXray* xray) { mVisXray = xray;}

};


#endif //PROJECT1__ITEMVISITOR_H
