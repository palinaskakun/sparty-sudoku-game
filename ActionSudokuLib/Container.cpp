/**
 * @file Container.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "Level.h"
#include "Container.h"
#include "ItemDigit.h"
#include "Visitors/ItemVisitor.h"

using namespace std;

/**
 * Constructor
 * @param level The level this object is in
 */
Container::Container(Level* level) : Item(level)
{
	mTileHeight = level->GetTileHeight();
	mTileWidth = level->GetTileWidth();
}

/**
 * Loads Xml tag
 * @param node the specific tag looked at
 */
void Container::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);

	mId = node->GetAttribute(L"id");

	node->GetAttribute(L"width").ToInt(&mWidth);
	node->GetAttribute(L"height").ToInt(&mHeight);
	node->GetAttribute(L"col").ToDouble(&mCol);
	node->GetAttribute(L"row").ToDouble(&mRow);


	//For testing
	mImageFile = node->GetAttribute(L"image", L"");
	mFrontImage = node->GetAttribute(L"front", L"");

	auto img1 = node->GetAttribute(L"image");
	auto img2 = node->GetAttribute(L"front");

	if (img1 != "")
	{
		auto filename1 = L"images/" + img1;
		auto filename2 = L"images/" + img2;

        mItemImg1 = make_shared<wxImage>(filename1, wxBITMAP_TYPE_ANY);
		mItemBitmap1 = make_shared<wxBitmap>(*mItemImg1);
		mItemImg2 = make_shared<wxImage>(filename2, wxBITMAP_TYPE_ANY);
		mItemBitmap2 = make_shared<wxBitmap>(*mItemImg2);
	}
}

/**
 * Draw the item.
 * @param graphics The drawing context to draw on.
 * @param width The height of the item
 * @param height The width of the item
 * @param bitmap the first bitmap of item
 * @param bitmap2 the second bitmap for the item
 * @param col the position of the item in terms of col
 * @param row the position of the item in terms of row
 */
void Container::Draw(shared_ptr<wxGraphicsContext> graphics, int width, int height,
					 std::shared_ptr<wxBitmap> bitmap, std::shared_ptr<wxBitmap> bitmap2, double col, double row)
{
	graphics->PushState();
	graphics->DrawBitmap(*bitmap,col*mTileWidth,(row+1)*mTileHeight-height, width, height);
	graphics->DrawBitmap(*bitmap2,col*mTileWidth,(row+1)*mTileHeight-height,width, height);
    graphics->PopState();

    mCurrentX = col*mTileWidth;
    mCurrentY = (row+1)*mTileHeight-height;
    mItemWidth = width;
    mItemHeight = height;
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void Container::Accept(ItemVisitor *visitor)
{
    Item::Accept(visitor);
    visitor->VisitContainer(this);
}

/**
 * Makes a list of digits inside the container
 * @param digit digit object that is put in a container
 */
void Container::HoldDigit(ItemDigit* digit) {
    holdingDigits.push_back(digit);
}
