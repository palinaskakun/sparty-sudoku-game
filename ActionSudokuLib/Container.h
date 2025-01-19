/**
 * @file Container.h
 * @author Team Syceus
 *
 * Class for Containers derived from Items
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_CONTAINER_H
#define PROJECT1_ACTIONSUDOKULIB_CONTAINER_H

#include "Item.h"

#include "Visitors/ItemVisitor.h"
#include <vector>

/**
 * Class for Containers derived from Items
 */
class Container : public Item
{
private:
	/// ID
	std::string mId;
	/// width
	int mWidth =0;
	/// height
	int mHeight =0;

	///Digits inside the container
	std::vector<std::shared_ptr<ItemDigit>> mContainerDigits;

    /// the front image when holding name
    std::string mFrontImage;
    /// image file when not holding name
	std::string mImageFile;

	/// image back bitmap
	std::shared_ptr<wxBitmap> mItemBitmap1;
	/// the container back image
	std::shared_ptr<wxImage> mItemImg1;
	/// the front bitmap of container
	std::shared_ptr<wxBitmap> mItemBitmap2;

	/// front image of container
	std::shared_ptr<wxImage> mItemImg2;

	/// Items in container
	std::vector<ItemDigit*> mDigits;

    ///  col position
	double mCol = 0;
    /// row position
    double mRow = 0;
    /// the x position
    double mCurrentX;
    /// the y position
    double mCurrentY;
	/// Tile width from xml
	int mTileWidth = 0;
	/// Tile height from xml
	int mTileHeight = 0;
    /// Items in container
    std::vector<ItemDigit*> holdingDigits;

public:
	Container(Level *level);
	void XmlLoad(wxXmlNode* node) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
			  std::shared_ptr<wxBitmap> bitmap, std::shared_ptr<wxBitmap> bitmap2, double col, double row) override;

    void HoldDigit(ItemDigit* digit);
    /**
     * getter for bitmap back
     * @return mItemBitmap1 member variable
     */
	std::shared_ptr<wxBitmap> GetBitmap() override { return mItemBitmap1; }
    /**
     * getter for bitmap front
     * @return mItemBitmap2 member variable
     */
	std::shared_ptr<wxBitmap> GetBitmap2() override { return mItemBitmap2; }

    /**
     * getter for image back
     * @return mImageFile member variable
     */
    std::string GetImageFile()  const { return mImageFile; }
    /**
     * getter for image front
     * @return mFrontImage member variable
     */
	std::string GetFrontImageFile() const { return mFrontImage; }

    /**
     * getter for digits that this contianer is holding
     * @return d member variable
     */
    std::vector<ItemDigit*> GetHoldingDigits() const { return holdingDigits; }
    /**
     * getter for container id
     * @return d member variable
     */
    std::string GetId() const {return mId; }

    /**
     * getter for container height
     * @return mHeight member variable
     */
    int GetHit() const {return mHeight; }

    /**
     * getter for container width
     * @return mWidth member variable
     */
    int GetWid() const {return mWidth; }

    /**
     * getter for container row pos
     * @return mRow member variable
     */
    double GetRow() const {return mRow; }

    void virtual Accept(ItemVisitor *visitor) override;

    /**
     * getter for current container x pos
     * @return mCurrentX member variable
     */
    double GetCurrentX() const { return mCurrentX; }
    /**
     * getter for current container y pos
     * @return mCurrentY member variable
     */
    double GetCurrentY() const { return mCurrentY; }
};

#endif //PROJECT1_ACTIONSUDOKULIB_CONTAINER_H
