/**
 * @file ItemCandy.h
 * @author Team Syceus
 *
 * Class for Candy Objects
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_ITEMCANDY_H
#define PROJECT1_ACTIONSUDOKULIB_ITEMCANDY_H

#include "Item.h"

/**
 * Class for Candy objects derived from item
 */
class ItemCandy : public Item

{
private:
//    /// width
//    int mWidth = 0;
//    /// height
//    int mHeight = 0;
//    /// value
//    int mValue = 0;
    /// if the candy has been eaten
    bool mIsEaten = false;
//    /// Tile width from xml
//    int mTileWidth = 0;
//    /// Tile height from xml
//    int mTileHeight = 0;

public:

    ItemCandy(Level *level);
    void XmlLoad(wxXmlNode* node) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
              std::shared_ptr<wxBitmap> bitmap1,
              std::shared_ptr<wxBitmap> bitmap2,
              double col, double row) override;

    void Accept(ItemVisitor *visitor) override;

    bool HitTest(double x, double y) override;

    /**
     * update mIsEaten member variable
     * @param eaten bool if eaten or not
     */
    void SetIsEaten(bool eaten) { mIsEaten = eaten; }

    /**
     * getter for if candy eaten
     * @return mIsEaten member variable
     */
    bool GetIsEaten() { return mIsEaten; };
};

#endif //PROJECT1_ACTIONSUDOKULIB_ITEMCANDY_H
