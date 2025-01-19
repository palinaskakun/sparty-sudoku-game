/**
 * @file ItemGiven.h
 * @author Team Syceus
 *
 * Class for Givens derived from items
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_ITEMGIVEN_H
#define PROJECT1_ACTIONSUDOKULIB_ITEMGIVEN_H

#include "Item.h"

/**
 * Class for Givens derived from items
 */
class ItemGiven : public Item
{
private:
//	/// width
//	int mWidth = 0;
//	/// height
//	int mHeight = 0;

	/// value
	int mValue = 0; // Also in item digit??

//	/// col
//	double mCol = 0;
//	/// row
//	double mRow = 0;
//	/// Tile width from xml
//	int mTileWidth = 0;
//	/// Tile height from xml
//	int mTileHeight = 0;


    // This is also in item digit??
	/// the col position of digit
	double mInitCol = 0;
	/// the row position of digit
	double mInitRow = 0;

public:
	ItemGiven(Level *level);
	void XmlLoad(wxXmlNode* node) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
				  std::shared_ptr<wxBitmap> bitmap1,
				  std::shared_ptr<wxBitmap> bitmap2,
				  double col, double row) override;

    void Accept(ItemVisitor *visitor) override;

    /**
     * getter for a given's value
     * @return int mValue member variable
     */
    int GetValue() const override{ return mValue; }

//    /**
//     * overriding the GetType from base class
//     * @return string of type
//     */
//    std::string GetType() const override {return "ItemGiven";}


    /**
     * resetting position
     */
	void ResetPosition() override;

};

#endif //PROJECT1_ACTIONSUDOKULIB_ITEMGIVEN_H