/**
 * @file ItemDigit.h
 * @author Team Syceus
 *
 * Class for Digits derived from items
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_ITEMDIGIT_H
#define PROJECT1_ACTIONSUDOKULIB_ITEMDIGIT_H


#include "Item.h"
#include <time.h>

/**
 * Class for Digits derived from items
 */

class ItemDigit : public Item
{
private:
//	/// width
//	int mWidth = 0;
//	/// height
//	int mHeight = 0;

	/// value
	int mValue = 0;

    /// graphics pointer
    std::shared_ptr<wxGraphicsContext> mGraphics;
    /// Check if m is eaten
    bool mIsEaten = false; // Redundancy: candy also has this attribute

//	/// Tile width from xml
//	int mTileWidth = 0;
//	/// Tile height from xml
//	int mTileHeight = 0;

    /// checking if item has popped
    bool hadPoped = false;
    /// value of column
    double mInitCol = 0.0;
    ///value of row
    double mInitRow = 0.0;

public:
    void Pop();

	ItemDigit(Level *level);
	void XmlLoad(wxXmlNode* node) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
				  std::shared_ptr<wxBitmap> bitmap1,
				  std::shared_ptr<wxBitmap> bitmap2,
				  double col, double row) override;

    void Accept(ItemVisitor *visitor) override;

    bool HitTest(double x, double y) override;

    void BeEaten(ItemXray* xray) override;

    /**
     * getter for a digit's value
     *  the digit we want value of
     * @return int mValue member variable
     */
    int GetValue() const override;

    /**
     * setter for value
     * @param value the new value
     */
    void SetValue(int value) { mValue = value; }
//	std::string GetType() const override {return "digit";}
    /**
     * getter for a digit's graphics context
     *  the digit we want value of
     * @return int mGraphics member variable
     */
    std::shared_ptr<wxGraphicsContext> GetGraphics() const {return mGraphics; }

    /**
     * setter for is eaten
     * @param eaten bool if eaten or not
     */
    void SetIsEaten(bool eaten) { mIsEaten = eaten; }

    /**
     * getter for is eaten
     * @return bool mIsEaten for status
     */
    bool GetIsEaten() { return mIsEaten; };

    bool OverlapTest(double col, double row);
    //bool GetIsEaten() { return mIsEaten; }
    /**
     * Function to reset position of digit
     */
	void ResetPosition() override;
   /**
    * Function to set position of digit
    * @param x
    * @param y
    */
	void SetPosition(double x, double y) override;
};

#endif //PROJECT1_ACTIONSUDOKULIB_ITEMDIGIT_H