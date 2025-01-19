/**
 * @file ItemXray.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "Level.h"
#include "ItemXray.h"
#include "ItemDigit.h"
#include <algorithm>

using namespace std;

/// within the Xray Image
const double XrayRange = 2.0;

/**
 * Constructor
 * @param level The level this object is in
 */
ItemXray::ItemXray(Level *level) : Item(level)
{
    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());

    mTileHeight = level->GetTileHeight();
    mTileWidth = level->GetTileWidth();
}

/**
 * Load the attributes for xray item node.
 *
 * @param node The Xml node we are loading the item from
 */
void ItemXray::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    node->GetAttribute(L"capacity").ToInt(&mCapacity);

//    node->GetAttribute(L"width").ToInt(&mWidth);
//    node->GetAttribute(L"height").ToInt(&mHeight);
//    node->GetAttribute(L"col").ToDouble(&mCol);
//    node->GetAttribute(L"row").ToDouble(&mRow);
}

/**
 * Draw the xray.
 * @param graphics The drawing context to draw on.
 * @param width The height of the item
 * @param height The width of the item
 * @param bitmap1 the first bitmap of item
 * @param bitmap2 the second bitmap for the item
 * @param col the position of the item in terms of col
 * @param row the position of the item in terms of row
 */
void ItemXray::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
                    std::shared_ptr<wxBitmap> bitmap1,
                    std::shared_ptr<wxBitmap> bitmap2,
                    double col, double row)
{

    graphics->PushState();
    graphics->DrawBitmap(*bitmap1, col * mTileWidth, (row - 1) * mTileHeight - mTileWidth, width, height);

    graphics->PopState();
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void ItemXray::Accept(ItemVisitor *visitor)
{
    Item::Accept(visitor);
    visitor->VisitXray(this);
}

bool ItemXray::RemoveNumber(int number, int row, int col)
{
    int index = -1;
    for (int i = 0; i < mEatenDigits.size(); i++)
    {
        if (mEatenDigits[i]->GetValue() == number)
        {
            index = i;
            break;
        }
    }

    if (mEatenDigits.size() > 0 && index >= 0)
    {
        mEatenDigits[index]->SetRow(row);
        mEatenDigits[index]->SetCol(col);
        mEatenDigits.erase(mEatenDigits.begin() + index);
        return true;
    }
    return false;
}

/**
 * adds digits to xray collection of eaten digits
 * @param digit pointer to digit items
 */
void ItemXray::Add(std::shared_ptr<ItemDigit> digit)
{
    mEatenHistory.push_back(digit);
    mEatenDigits.push_back(&*digit);

    std::uniform_real_distribution<> distributionCol(mCol, mCol+XrayRange);
    auto newCol = distributionCol(GetRandom());

    std::uniform_real_distribution<> distributionRow(mRow-XrayRange, mRow);
    auto newRow = distributionRow(GetRandom());

/*    OverlapChecker overlapCheck;

    // Need something to accept the visitor so that each item will be visited

    if(overlapCheck.Overlaps())
    {
        newCol = distributionCol(GetRandom());
        newRow = distributionRow(GetRandom());
    }*/

    digit->SetCol(newCol);
    digit->SetRow(newRow);
}

/**
 * Checks if Sparty's stomach is full
 * @return bool true if present else false
 */
bool ItemXray::IsFull()
{
    if (mEatenDigits.size() < mCapacity)
    {
        return false;
    }
    return true;

}
