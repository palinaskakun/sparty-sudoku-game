/**
 * @file Item.cpp
 * @author Team Syceus
 */
#include "pch.h"
#include "Item.h"
#include "Level.h"
#include "Visitors/ItemVisitor.h"

using namespace std;


Item::Item(Level *level) : mLevel(level)
{
    mTileHeight = level->GetTileHeight();
    mTileWidth = level->GetTileWidth();
}

/**
 * Draws item
 * @param graphics The drawing context to draw on.
 * @param width The height of the item
 * @param height The width of the item
 * @param bitmap1 the first bitmap of item
 * @param bitmap2 the second bitmap for the item
 * @param col the position of the item in terms of col
 * @param row the position of the item in terms of row
 */
void Item::Draw(shared_ptr<wxGraphicsContext> graphics, int width, int height,
				std::shared_ptr<wxBitmap> bitmap1, std::shared_ptr<wxBitmap> bitmap2, double col, double row)
{

}

/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* @param node The Xml node we are loading the item from
*/
void Item::XmlLoad(wxXmlNode* node)
{
	mId = node->GetAttribute(L"id");
	node->GetAttribute(L"width").ToInt(&mItemWidth);
	node->GetAttribute(L"height").ToInt(&mItemHeight);
	node->GetAttribute(L"col").ToDouble(&mCol);
	node->GetAttribute(L"row").ToDouble(&mRow);

	//For testing
	mImageFile = node->GetAttribute(L"image", L"");

	auto img = node->GetAttribute(L"image");

	if (img != "")
	{
		auto filename = L"images/" +
			node->GetAttribute(L"image");
		mItemImage = make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
		mItemBitmap = make_shared<wxBitmap>(*mItemImage);
  	}
}

/**
 * Updates Item position
 * @param x x value new
 * @param y y value new
 */
void Item::SetPosition(double x, double y)
{
    mX = x;
    mY = y;
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void Item::Accept(ItemVisitor *visitor)
{
    visitor->VisitItem(this);
}

/**
 * Destructor.
 */
Item::~Item()
{
}