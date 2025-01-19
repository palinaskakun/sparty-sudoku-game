/**
 * @file Sparty.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "Sparty.h"
#include "Visitors/ItemVisitor.h"
#include "Level.h"
#include <random>

using namespace std;

/// Character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.6;

/// the rotation amount for headbutt
const double HeadbuttRotationIncrement = 0.2;

/// the rotation amount for eat
const double EatRotationIncrement = 0.2;

/**
 * constructor
 * @param level the level for which sparty is to be constructed
 */
Sparty::Sparty(Level *level) : Item(level)
{
    mTileHeight = level->GetTileHeight();
    mTileWidth = level->GetTileWidth();

}

/**
 * Load the attributes for a sparty item node.
 *
 * @param node The Xml node we are loading the item from
 */
void Sparty::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    auto img1 = node->GetAttribute(L"image1");
    auto img2 = node->GetAttribute(L"image2");
    if(img1 != "")
    {
        auto filename1 = L"images/" + img1;
        auto filename2 = L"images/" + img2;
        mItemImage1 = make_shared<wxImage>(filename1, wxBITMAP_TYPE_ANY);
        mItemBitmap1 = make_shared<wxBitmap>(*mItemImage1);
        mItemImage2 = make_shared<wxImage>(filename2, wxBITMAP_TYPE_ANY);
        mItemBitmap2 = make_shared<wxBitmap>(*mItemImage2);
    }

    node->GetAttribute(L"front").ToInt(&mFront);
    node->GetAttribute(L"head-pivot-angle").ToDouble(&mHeadPivotAngle);
    node->GetAttribute(L"mouth-pivot-angle").ToDouble(&mMouthPivotAngle);
    node->GetAttribute(L"head-pivot-x").ToInt(&mHeadPivot.x);
    node->GetAttribute(L"head-pivot-y").ToInt(&mHeadPivot.y);

    node->GetAttribute(L"mouth-pivot-x").ToInt(&mMouthPivot.x);
    node->GetAttribute(L"mouth-pivot-y").ToInt(&mMouthPivot.y);

    node->GetAttribute(L"target-x").ToInt(&mTargetX);
    node->GetAttribute(L"target-y").ToInt(&mTargetY);
}

/**
 * Draw Sparty
 * @param graphics the graphics context to draw in
 * @param width the width of sparty image
 * @param height the height of sparty image
 * @param bitmap1 the first bitmap for sparty
 * @param bitmap2 the second bitmap for sparty
 * @param col the col position for sparty
 * @param row the row position for sparty
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
                  std::shared_ptr<wxBitmap> bitmap1,
                  std::shared_ptr<wxBitmap> bitmap2,
                  double col, double row)
{
    graphics->PushState();

    double defaultX = col * mTileWidth;
    double defaultY = (row + 1) * mTileHeight;

    double renderX;
    double renderY;

    if(mLocation.x == 0.0)
    {
        renderX = defaultX;
        renderY = defaultY;

        mLocation.x = defaultX;
        mLocation.y = defaultY;
        mTarget.x = mLocation.x;
        mTarget.y = mLocation.y;
    }
    else
    {
        renderX = mLocation.x;
        renderY = mLocation.y;
    }

    mItemWidth = width;
    mItemHeight = height;

    if(mShouldStartHeadButt)
    {
        // HeadButt animation
        double locationX = (renderX) - width + width / 4;
        double locationY = (renderY) - width + width / 4;
        graphics->Translate(locationX + mHeadPivot.x / 2, locationY + mHeadPivot.y);
        graphics->Rotate(mHeadPivotAngle);
        graphics->DrawBitmap(*bitmap1, -mHeadPivot.x / 2, -mHeadPivot.y, width, height);
        graphics->DrawBitmap(*bitmap2, -mHeadPivot.x / 2, -mHeadPivot.y, width, height);

        graphics->Rotate(-mHeadPivotAngle);
        graphics->Translate(-(locationX + mHeadPivot.x / 2), -(locationY + mHeadPivot.y));
        if(mHeadPivotAngle >= HeadbuttTime)
        {
            mRotateRight = false;
        }
        if(mHeadPivotAngle < 0)
        {
            mRotateRight = true;
            mShouldStartHeadButt = false;
        }
        mHeadPivotAngle = mRotateRight ? (mHeadPivotAngle + HeadbuttRotationIncrement) :
            (mHeadPivotAngle - HeadbuttRotationIncrement);

    }
    else if(mShouldStartEating)
    {
        double locationX = (renderX) - width + width / 4;
        double locationY = (renderY) - width + width / 4;
        graphics->Translate(locationX + mHeadPivot.x, locationY + mHeadPivot.y);
        graphics->DrawBitmap(*bitmap1, -mHeadPivot.x, -mHeadPivot.y, width, height);
        graphics->Rotate(mMouthPivotAngle);

        graphics->DrawBitmap(*bitmap2, -mHeadPivot.x, -mHeadPivot.y, width, height);

        graphics->Rotate(-mMouthPivotAngle);
        graphics->Translate(-(locationX + mHeadPivot.x), -(locationY + mHeadPivot.y));

        if(mMouthPivotAngle > EatingTime)
        {
            mRotateRight = false;
        }
        if(mMouthPivotAngle < 0)
        {
            mRotateRight = true;
            mShouldStartEating = false;
        }
        mMouthPivotAngle =
            mRotateRight ? (mMouthPivotAngle + EatRotationIncrement) : (mMouthPivotAngle - EatRotationIncrement);
    }
    else
    {
        // Sparty movement animation
        graphics->DrawBitmap(*bitmap1, (renderX) - width + width / 4, (renderY) - height + height / 4, width, height);
        graphics->DrawBitmap(*bitmap2, (renderX) - width + width / 4, (renderY) - height + height / 4, width, height);
    }

    graphics->PopState();
}

/**
 * updates location of sparty via vector continuous movement
 * @param elapsed  the time elapsed
 */
void Sparty::Update(double elapsed)
{
    // Vector pointing in the direction we want to move
    wxRealPoint d(mTarget.x - mLocation.x, mTarget.y - mLocation.y);

    // Distance to the target
    double distance = sqrt(d.x * d.x + d.y * d.y);

    if(distance < 1.0)
    {
        mLocation = mTarget;
        return;
    }

    // Normalize the direction vector
    double dx = d.x / distance;
    double dy = d.y / distance;

    // Determine how far we move in this time step
    double moveDistance = MaxSpeed * elapsed;
    if(moveDistance > distance)
    {
        mLocation = mTarget;
    }
    else
    {
        mLocation.x += dx * moveDistance;
        mLocation.y += dy * moveDistance;
    }
}

/**
 * updates wanted/target location of sparty
 * @param x new target x location
 * @param y new target y location
 */
void Sparty::SetPosition(double x, double y)
{
    mTarget.x = x;
    mTarget.y = y;
}


void Sparty::SetHeadPivot(wxPoint pivot)
{
    mHeadPivot = pivot;
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void Sparty::Accept(ItemVisitor *visitor)
{
    Item::Accept(visitor);
    visitor->VisitSparty(this);
}

/**
 * Eating the number
 */
void Sparty::Eat()
{
    mShouldStartEating = true;
}

/**
 * Headbutting the number
 */
void Sparty::HeadButt()
{
    mShouldStartHeadButt = true;
}


/**
 * vomitting the number
 */
void Sparty::Vomit()
{

}

/**
 * resets the postion of sparty
 */
void Sparty::ResetPosition()
{
    mLocation.x = 0;
    mLocation.y = 0;
    mTarget.x = mLocation.x;
    mTarget.y = mLocation.y;

}
