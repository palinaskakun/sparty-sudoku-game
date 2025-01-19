/**
 * @file ItemGiven.cpp
 * @author Palina Skakun
 */

#include "pch.h"
#include "Level.h"
#include "ItemGiven.h"
#include "Visitors/ItemVisitor.h"

using namespace std;
/**
 * Constructor
 * @param level The level this object is in
 */
ItemGiven::ItemGiven(Level* level) : Item(level)
{
//	mTileHeight = level->GetTileHeight();
//	mTileWidth = level->GetTileWidth();

}

/**
 *
 * @param node
 */
void ItemGiven::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);

	node->GetAttribute(L"value").ToInt(&mValue);
	node->GetAttribute(L"col").ToDouble(&mCol);
	node->GetAttribute(L"row").ToDouble(&mRow);

	mInitCol = mCol;
	mInitRow = mRow;
}

/**
 * Draw the given.
 * @param graphics The drawing context to draw on.
 * @param width The height of the item
 * @param height The width of the item
 * @param bitmap1 the first bitmap of item
 * @param bitmap2 the second bitmap for the item
 * @param col the position of the item in terms of col
 * @param row the position of the item in terms of row
 */
void ItemGiven::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
					 std::shared_ptr<wxBitmap> bitmap1,
					 std::shared_ptr<wxBitmap> bitmap2,
					 double col, double row)
{

	graphics->PushState();
	graphics->DrawBitmap(*bitmap1,col*48,row*48,width, height);

	graphics->PopState();
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void ItemGiven::Accept(ItemVisitor *visitor)
{
    Item::Accept(visitor);
    visitor->VisitGiven(this);
}


void ItemGiven::ResetPosition()
{
	mCol = mInitCol;
	mRow = mInitRow;

}


