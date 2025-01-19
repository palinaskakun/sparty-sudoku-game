/**
 * @file Item.h
 * @author Team Syceus
 *
 * The base class for all items
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_ITEM_H
#define PROJECT1_ACTIONSUDOKULIB_ITEM_H

#include <wx/xml/xml.h>
#include <wx/graphics.h>


class Level;
class ItemVisitor;
class ItemXray;

/**
 * The base class for all items in the game
 */
class Item
{
private:
    /// Level associated with this item
    Level *mLevel;

	/// Underlying item image.
    std::shared_ptr<wxImage> mItemImage;

    /// Underlying front item image.
    std::shared_ptr<wxImage> mItemImageFront;

	/// Underlying bitmap for image.
	std::shared_ptr<wxBitmap> mItemBitmap;

    /// Underlying front bitmap for image.
    std::shared_ptr<wxBitmap> mItemBitmapFront;

    // Item location in the board
    double  mX = 0;    ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

//    // Do we need this if we have itemwidth???
//	double mWidth = 0;  ///< Width of the item
//	double mHeight = 0; ///< Height of the item

	///for testing filename
	std::string mImageFile;

	//ActionSudoku *mActionSudoku;
	std::string mId; ///< the id of the item

    // do we need this here?? Only digit and given uses it
    int mValue; ///< the value of the item



protected:
    int mTileWidth = 0; ///< Width of the tile
    int mTileHeight = 0; ///< Width of tile

    int mItemWidth = 0;  ///< Width of the item
    int mItemHeight = 0; ///< Height of the item

    double mCol = 0; ///< the col position of item
    double mRow = 0; ///< the row position of the item

public:
	/// Default constructor disabled
	Item() = delete;
	/// Copy constructor disabled
	Item(const Item&) = delete;

	/// Assignment operator disabled.
	void operator=(const Item &) = delete;

    /**
     * virtual hittest fcn for all items, can be overriden by derived class
     * @param x the x coordinate tested
     * @param y the y coordinate tested
     * @return the bool to indicate if false
     */
    virtual bool HitTest(double x, double y) { return false; }

	/// Destructor.
	virtual ~Item();

    /**
     * for items in level
     * @param level
     */
	Item (Level* level);

	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
					  std::shared_ptr<wxBitmap> bitmap1,
					  std::shared_ptr<wxBitmap> bitmap2,
					  double col, double row);

	virtual void XmlLoad(wxXmlNode* node);

    /**
     * virutal function of to be eaten, can be overrided by derived classes
     * @param xray the new place to be poistioned
     */
    virtual void BeEaten(ItemXray* xray) {};

    /**
     * getter for item id
     * @return mId member varible
     */
	std::string GetId() const {return mId;}

    /**
     * getter for item col position
     * @return mCol member variable
     */
	double GetCol() const {return mCol;}

    /**
     * getter for item row position
     * @return mRow member variable
     */
	double GetRow() const {return mRow;}

    /**
     * getter for item width
     * @return mItemWidth member variable
     */
	int GetItemWidth() const { return mItemWidth; }

    /**
     * getter for item height
     * @return mItemHeight member variable
     */
	int GetItemHeight() const { return mItemHeight;}

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }


	/**
	 * The bitmap back for this item
	 * @return mItemBitmap member variable
	 */
	virtual std::shared_ptr<wxBitmap> GetBitmap() { return mItemBitmap; }

    /**
	 * The bitmap front for this item
	 * @return mItemBitmapFront member variable
	 */
	virtual std::shared_ptr<wxBitmap> GetBitmap2() { return mItemBitmapFront; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(ItemVisitor* visitor);



	/**
	 * Handle updates for animation
	 * @param elapsed The time since the last update in seconds
	 */
	virtual void Update(double elapsed) {}

	/**
     * Get the level that item is in.
     * @return The level this item is contained in.
     */
	Level* GetLevel() { return mLevel; }

    /**
     * virtual fcn to update location, can be override by derived classes
     */
	virtual void SetPosition(double x, double y);

    /// be eaten virtual fcn, can be override
    virtual void BeEaten() {}

    /**
     * getter for image file
     * @return mImageFile member variable
     */
	std::string GetImageFile() { return mImageFile; }

    //std::shared_ptr<wxImage> GetImage() { return mItemImage; }

    /**
     * virtual getter for type, van be override by derived classes
     * @return string of type
     */

//    virtual std::string GetType() const {return "Item";}

    /**
     * virtual getter for value, can be override by derived classes
     * @return int mValue member variable
     */
    virtual int GetValue() const { return mValue; }

    /**
     * virtual setter for col, can override by derived classes
     * @param col the new col value
     */
    virtual void SetCol(double col) { mCol = col; }

    /**
      * virtual setter for row, can override by derived classes
      * @param row the new row value
      */
    virtual void SetRow(double row) { mRow = row; }

    /**
     * resets position of item, can override since virtua l
     */
	virtual void ResetPosition () { }

	/**
	 * getter for target offset value, can override by derived classes
	 * @return wxPoint pt variable
	 */
	virtual wxPoint GetTargetOffset() const {wxPoint pt; pt.x = 0; pt.y = 0; return pt;}

    /**
     * sets the xrays capacity
     * @param capacity the new capacity of xray
     */
    virtual void SetXrayCapacity(int capacity) {}

	/**
	 * gets xray's capacity
	 * @return int capacity of the xray
	 */
	virtual int GetXrayCapacity() const {return 0;}

    /**
     * the setter for target offset values
     * @param x new x value
     * @param y new y value
     */
	virtual void SetTargetOffset(int x, int y) {}

};

#endif //PROJECT1_ACTIONSUDOKULIB_ITEM_H
