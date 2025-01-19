/**
 * @file ItemXray.h
 * @author Team Syceus
 *
 * Class for xray derived from item
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_ITEMXRAY_H
#define PROJECT1_ACTIONSUDOKULIB_ITEMXRAY_H

#include "Item.h"
#include "Visitors/ItemVisitor.h"
#include <vector>
#include <random>

class Level;

/**
 * Class for Xray derived from item
 */
class ItemXray : public Item
{
private:
//	/// width
//	int mWidth = 0;
//	/// height
//	int mHeight = 0;
	/// capacity
	int mCapacity = 0;
//	/// col
//	double mCol = 0;
//	/// row
//	double mRow = 0;
//	/// Tile width from xml
//	int mTileWidth = 0;
//	/// Tile height from xml
//	int mTileHeight = 0;

    /// Random number generator
    std::mt19937 mRandom;

public:
    /// Items eaten by Sparty / in the Xray
    std::vector<std::shared_ptr<ItemDigit>> mEatenHistory;
    /// The digits that are eaten
    std::vector<ItemDigit*> mEatenDigits;

	ItemXray(Level *level);
	void XmlLoad(wxXmlNode *node) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
			  std::shared_ptr<wxBitmap> bitmap1,
			  std::shared_ptr<wxBitmap> bitmap2,
			  double col, double row) override;

    void Accept(ItemVisitor *visitor) override;

    /**
     * getter for capacity
     * @return mCapacity member variable
     */
    int GetCapacity() const {return mCapacity;}

    void Add(std::shared_ptr<ItemDigit> digit);

    bool IsFull();
    /**
     * boolean if number should be removed
     * @param number
     * @param row
     * @param col
     * @return
     */
    bool RemoveNumber(int number, int row, int col);

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}

	/**
	 *
	 * @param capacity
	 */
	void SetXrayCapacity(int capacity) override {mCapacity = capacity;}

	/**
	 *
	 * @return the capacity of xray
	 */
	int GetXrayCapacity() const override {return mCapacity;}
    /**
     * function for resetting position of digits
     */
	void ResetPosition() override {mEatenDigits.clear();};
};

#endif //PROJECT1_ACTIONSUDOKULIB_ITEMXRAY_H