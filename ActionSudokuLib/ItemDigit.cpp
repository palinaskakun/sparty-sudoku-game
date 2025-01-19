/**
 * @file ItemDigit.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "Level.h"
#include "ItemDigit.h"
#include "Visitors/ItemVisitor.h"

using namespace std;
///Upper bound of range for digit to draw
const int UpperBound = 300;
///Lower bound of range for digit to draw
const int LowerBound = 100;
///Offset for drawing the digit in the new spot
const double BoundOffset = 1.5;

/**
 * Constructor
 * @param level The level this object is in
 */
ItemDigit::ItemDigit(Level* level) : Item(level)
{
//	mTileHeight = level->GetTileHeight();
//	mTileWidth = level->GetTileWidth();
}

/**
 * Load the attributes for a digit item node.
 *
 * @param node The Xml node we are loading the item from
 */
void ItemDigit::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);

	node->GetAttribute(L"value").ToInt(&mValue);
	node->GetAttribute(L"col").ToDouble(&mCol);
	node->GetAttribute(L"row").ToDouble(&mRow);

	mInitCol = mCol;
	mInitRow = mRow;
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
void ItemDigit::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
					 std::shared_ptr<wxBitmap> bitmap1,
					 std::shared_ptr<wxBitmap> bitmap2,
					 double col, double row)
{
    mGraphics = graphics;

	graphics->PushState();
	graphics->DrawBitmap(*bitmap1,mCol*mTileWidth,mRow*mTileHeight,width, height);

    graphics->PopState();
}

int ItemDigit::GetValue() const {
    return mValue;
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void ItemDigit::Accept(ItemVisitor *visitor)
{
    Item::Accept(visitor);
    visitor->VisitDigit(this);
}

/**
 * Checks if the coordinates are next to this digit.
 * @param x x coordinate in pixels
 * @param y y coordinate in pixels
 * @return
 */
bool ItemDigit::HitTest(double x, double y)
{
    if (mIsEaten)
    {
        return false;
    }
    //return false;

    //making x & y relative to top left
    // (col*tileHeight, (row-1)*tileHeight-height) according to level description/interact

    double topLeftX = (mCol)*mTileHeight;
    double topLeftY = (mRow)*mTileHeight;



    double halfTile = mTileWidth / 2;

    double middleX = topLeftX + halfTile;
    double middleY = (mRow)*mTileHeight - halfTile;

//    if ((x < topLeftX - halfTile) || (x > topLeftX + halfTile) || (y < topLeftY - halfTile) || (y > topLeftY + mTileHeight + halfTile))
//
//	{
//        // we are outside the tile and not within 0.5 tiles
//        return false;
//    }

	if ((x < topLeftX - halfTile) || (x > topLeftX + mTileWidth) || (y < topLeftY - halfTile) || (y > topLeftY + mTileHeight + halfTile))

	{
		// we are outside the tile and not within 0.5 tiles
		return false;
	}

    return true;
}


/**
 * Checks if the coordinates are on digit/match.
 * @param col coordinate in col
 * @param row coordinate in row
 * @return
 */
bool ItemDigit::OverlapTest(double col, double row)
{
    if (((mCol < col + 0.5 && mCol > mCol-0.5)) && ((mRow < row + 0.5) && (mRow > row -0.5)))
    {
        return true;
    }
    return false;
}

/**
 * updating digit to xray as eaten
 * @param xray the new placement of the digit
 */
void ItemDigit::BeEaten(ItemXray *xray)
{
    xray->Add(std::shared_ptr<ItemDigit>(this));
}

/**
 * Updating digit's row and col to be random when Sparty hits the container
 */
void ItemDigit::Pop()
{
    double randomRow = ((rand() % UpperBound) / LowerBound) + BoundOffset; //1.0 ~ 4.0
    double randomCol = ((rand() % UpperBound) / LowerBound); //0.0 ~ 3.0
    if(!hadPoped) {
        mRow -= randomRow;
        mCol += (int)randomCol % 2 == 0 ? randomCol : -randomCol;
    }
    hadPoped = true;
}

void ItemDigit::SetPosition(double col, double row)
{
	mCol = col;
	mRow = row;

}

/**
 *
 */
void ItemDigit::ResetPosition()
{
	mCol = mInitCol;
	mRow = mInitRow;

}

///**
// * Destructor.
// */
//ItemDigit::~ItemDigit()
//{
//}