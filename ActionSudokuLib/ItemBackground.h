/**
 * @file ItemBackground.h
 * @author Team Syceus
 *
 *
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_ITEMBACKGROUND_H
#define PROJECT1_ACTIONSUDOKULIB_ITEMBACKGROUND_H

#include "Item.h"

/**
 * Class for a background item
 */
class ItemBackground : public Item
{
private:
    /// scale for background item
	double mScale = 0;
	/// X offset
	double mXOffset = 0;
	/// Y offset
	double mYOffset = 0;

    // are we allowed to use 48 like this? (levels description of project talks about it but idk if i understand right? - pp

	///Filename for testing
	std::string mImageFile;

public:
	ItemBackground(Level* level);
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height,
			  std::shared_ptr<wxBitmap> bitmap1,
			  std::shared_ptr<wxBitmap> bitmap2,
			  double col, double row) override;
	void XmlLoad(wxXmlNode* node) override;

    /**
     * getter for background image file
     * @return mImageFile member variable
     */
	std::string GetImageFile() { return mImageFile; }
};

#endif //PROJECT1_ACTIONSUDOKULIB_ITEMBACKGROUND_H