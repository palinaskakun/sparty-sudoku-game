/**
 * @file ItemBackground.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "ItemBackground.h"
#include "Item.h"
#include "ActionSudoku.h"

using namespace std;
/**
 * Constructor
 * @param level The level this object is in
 */
ItemBackground::ItemBackground(Level* level) : Item(level)
{
	mTileHeight = level->GetTileHeight();
	mTileWidth = level->GetTileWidth();
}

/**
 * Load the attributes for the background
 *
 * @param node The Xml node we are loading the item from
 */
void ItemBackground::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);

	//For testing
	mImageFile = node->GetAttribute(L"image", L"");

}

/**
 * Draw the background.
 * @param graphics The drawing context to draw on.
 * @param width The height of the item
 * @param height The width of the item
 * @param bitmap1 the first bitmap of item
 * @param bitmap2 the second bitmap for the item
 * @param col the position of the item in terms of col
 * @param row the position of the item in terms of row
 */
void ItemBackground::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
						  std::shared_ptr<wxBitmap> bitmap1,
						  std::shared_ptr<wxBitmap> bitmap2,
						  double col, double row)
{
	graphics->PushState();
	graphics->DrawBitmap(*bitmap1,col*mTileWidth,(row+1)*mTileHeight-height,width, height);


	graphics->PopState();
}