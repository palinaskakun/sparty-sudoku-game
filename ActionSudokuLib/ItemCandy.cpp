/**
 * @file ItemCandy.cpp
 * @author pp
 */

#include "pch.h"
#include "Level.h"
#include "ItemCandy.h"
#include "Visitors/ItemVisitor.h"

using namespace std;


/**
 * Constructor
 * @param level The level this object is in
 */
ItemCandy::ItemCandy(Level* level) : Item(level)
{
//    mTileHeight = level->GetTileHeight();
//    mTileWidth = level->GetTileWidth();
}

/**
 * Load the attributes for a candy item node.
 *
 * @param node The Xml node we are loading the item from
 */
void ItemCandy::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    //node->GetAttribute(L"value").ToInt(&mValue);
//    node->GetAttribute(L"col").ToDouble(&mCol);
//    node->GetAttribute(L"row").ToDouble(&mRow);
}

/**
 * Draw the digit.
 * @param graphics The drawing context to draw on.
 * @param width The height of the item
 * @param height The width of the item
 * @param bitmap1 the first bitmap of item
 * @param bitmap2 the second bitmap for the item
 * @param col the position of the item in terms of col
 * @param row the position of the item in terms of row
 */
void ItemCandy::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
                     std::shared_ptr<wxBitmap> bitmap1,
                     std::shared_ptr<wxBitmap> bitmap2,
                     double col, double row)
{
    if (!mIsEaten)
    {
        graphics->PushState();
        graphics->DrawBitmap(*bitmap1,col*mTileWidth,row*mTileHeight,width, height);

        graphics->PopState();

    }

}


/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void ItemCandy::Accept(ItemVisitor *visitor)
{
    Item::Accept(visitor);
    visitor->VisitCandy(this);
}

/**
 * Checks if the coordinates are next to this digit.
 * @param x x coordinate in pixels
 * @param y y coordinate in pixels
 * @return
 */
bool ItemCandy::HitTest(double x, double y)
{
    if (mIsEaten)
    {
        return false;
    }
    double topLeftX = (mCol)*mTileHeight;
    double topLeftY = (mRow)*mTileHeight;

    double halfTile = mTileWidth / 2;

    double middleX = topLeftX + halfTile;
    double middleY = (mRow)*mTileHeight - halfTile;

    if ((x < topLeftX - halfTile) || (x > topLeftX + halfTile) || (y < topLeftY - halfTile) || (y > topLeftY + mTileHeight + halfTile))
    {
        // we are outside the tile and not within 0.5 tiles
        return false;
    }

    return true;
}