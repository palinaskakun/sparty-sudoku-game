/**
 * @file Sparty.h
 * @author Team Syceus
 *
 * Class for Sparty figure
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_SPARTY_H
#define PROJECT1_ACTIONSUDOKULIB_SPARTY_H

#include "Item.h"
#include "ItemXray.h"

/**
 * Compound Sparty Class for the sparty figure
 */
class Sparty : public Item
{
private:

    wxRealPoint mLocation;  ///< Current location of Sparty
    wxRealPoint mTarget;    ///< Target location for Sparty to move to
	/**
     * The bitmap we can display for the Sparty's mouth
     * The other bitmap is Sparty's head
     */
	std::shared_ptr<wxBitmap> mItemBitmap1;

	/**
	 * The underlying image for Sparty's mouth
	 * The other image is Sparty's head
	 */
	std::shared_ptr<wxImage> mItemImage1;
    /**
     * The bitmap we can display for the Sparty's mouth
     * The other bitmap is Sparty's head
     */
    std::shared_ptr<wxBitmap> mItemBitmap2;

    /**
     * The underlying image for Sparty's mouth
     * The other image is Sparty's head
     */
    std::shared_ptr<wxImage> mItemImage2;

    /// the front value
    int mFront = 0;
    /// the width of sparty
    int mWidth = 0;
    /// the height of sparty
    int mHeight = 0;

    /// The angle in radians the mouth rotates clockwise to starting at 0 radians
    double mMouthPivotAngle=0;
    /// The pivot point the mouth rotates around
    wxPoint mMouthPivot;

    /// The angle in radians the head rotates clockwise to starting at 0 radians
    double mHeadPivotAngle=0;
    /// The pivot point the head rotates around
    wxPoint mHeadPivot;

    /// Sparty should move to the location offset by the value of target-x, target-y
    wxPoint mTargetOffset;

    /// id number of sparty
    std::string mId;

    /// the col position of sparty
	double mCol = 0;
    /// the row position of sparty
	double mRow = 0;

	/// Tile width
	int mTileWidth = 0;
	/// Tile Height
	int mTileHeight = 0;

	/// the col position of sparty
	double mInitCol = 0;
	/// the row position of sparty
	double mInitRow = 0;


    /// indication if rotating right
    bool mRotateRight = true;
    /// indication if should headbutt
    bool mShouldStartHeadButt = false;
    /// indication if should eat
    bool mShouldStartEating = false;


	/// Sparty should move to the location offset by the value of target-x
	int mTargetX =0;
	/// Sparty should move to that location offset by the value of target-y
	int mTargetY=0;


public:
	///Disable default constructor
	Sparty() = delete;
	///Disable copy constructor
	Sparty(const Sparty &) = delete;
	///Disable assignment operator
	void operator=(const Sparty &) = delete;

	Sparty(Level* level);
	void XmlLoad(wxXmlNode* node) override;

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
			  std::shared_ptr<wxBitmap> bitmap1,
			  std::shared_ptr<wxBitmap> bitmap2,
			  double col, double row) override;

	/**
	 * The bitmap for this item
	 * @return The wxBitmap for this item
	 */
	std::shared_ptr<wxBitmap> GetBitmap() override { return mItemBitmap1; }

	/**
	 * The bitmap for this item
	 * @return The wxBitmap for this item
	 */
	std::shared_ptr<wxBitmap> GetBitmap2() override { return mItemBitmap2; }

    /**
     * Trigger the eating animation
     */
    void Eat();
    /**
     * Headbutting the number
     */
    void HeadButt();
    /**
    * vomitting the number
    */
    void Vomit();

    void SetPosition(double x, double y) override;

	void Update(double elapsed) override;
    void Accept(ItemVisitor* visitor) override;

    /**
     * getter for target x coordinate
     * @return mTarget.x member variable
     */
	double GetTargetX() const { return mTarget.x; }
    /**
     * getter for target y coordinate
     * @return mTarget.y member variable
     */
	double GetTargetY() const { return mTarget.y; }

    /**
     * getter for current x coordinate
     * @return mLocation.x member variable
     */
    double GetCurrentX() const { return mLocation.x; }
    /**
     * getter for current y coordinate
     * @return mLocation.y member variable
     */
    double GetCurrentY() const { return mLocation.y; }

    /**
     * getter for sparty width
     * @return mItemWidth member variable
     */
    int GetItemWidth() const { return mItemWidth; }
    /**
     * getter for sparty height
     * @return mItemHeight member variable
     */
    int GetItemHeight() const { return mItemHeight; }

    /**
     * getter for sparty bitmap height
     * @return double bitmap height
     */
	double GetBitmapHeight() const {return mItemBitmap2->GetHeight();}

    /**
     * getter for sparty bitmap width
     * @return double bitmap width
     */
	double GetBitmapWidth() const {return mItemBitmap2->GetWidth();}

    /**
     * getter for sparty head pivot
     * @return mHeadPivot head pivot
     */
    wxPoint GetHeadPivot() const { return  mHeadPivot; }

    /**
     *  Function on mouse is clicked
     * @param graphics
     */
	void OnKeyDown(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * setting the head pivot
     * @param pivot
     */
    void SetHeadPivot(wxPoint pivot);

    /**
     * function for resetting the position for sparty
     */
	void ResetPosition () override;

	/**
    * getter for target x coordinate
    * @return mTarget.x member variable
    */
	wxPoint GetTargetOffset() const override { return mTargetOffset; }

	/**
	 * returning offsets
	 * @param x
	 * @param y
	 */
	virtual void SetTargetOffset(int x, int y) override { mTargetOffset.x = x; mTargetOffset.y = y;}

};

#endif //PROJECT1_ACTIONSUDOKULIB_SPARTY_H
