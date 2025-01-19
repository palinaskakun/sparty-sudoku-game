/**
 * @file ActionSudoku.h
 * @author Team Syceus
 *
 * The main game class.
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_ACTIONSUDOKU_H
#define PROJECT1_ACTIONSUDOKULIB_ACTIONSUDOKU_H

#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <wx/graphics.h>

#include "LevelLoader.h"
#include "Visitors/ItemVisitor.h"
#include "Scoreboard.h"

/**
 * The main game class.
 */
class ActionSudoku
{
private:
    /// current level pointer
	std::unique_ptr<Level> mCurrentLevel;

    /// scoreboard/timer pointer
	std::unique_ptr<Scoreboard> mScoreboardTimer;

	/// Level pointer to levels
	std::shared_ptr<LevelLoader> mLevelLoader;
	/// calculate scale from width and height
	double mScale = 0;
	/// X axis offset
	double mXOffset = 0;
	/// Y axis offset
	double mYOffset = 0;
	/// (CHANGE THIS NUMBER TO 20 TO SEE LEVEL 2 PROPERLY) Height for given in xml, not loaded yet
	int mHeight = 0;
	/// Level of game
	int mLevel = 1;
	/// (CHANGE THIS NUMBER TO 30 SEE LEVEL 2 PROPERLY) width given in xml but not loaded yet
	int mWidth = 0;
	/// tile height from XML
	int mTileHeight = 0;
	/// tile width from XML
	int mTileWidth = 0;

    // Mouse position X, Y
	// Location where sparty first goes (should appear here)
    /// mouse input in x
	int mInputMouseX = 0;
    /// mouse input in y
	int mInputMouseY = 0;

	/// vector of pointers from Level class to levels
	std::vector<std::shared_ptr<Level>> mLevels;
    /// pointer to level 1
	std::shared_ptr<Level> mLevel1;
	///Timer for transitioning
	wxTimer mTransitionTimer;

public:
	ActionSudoku();

    /**
     * Gets the size of the level
     * @return wxSize object for size
     */
	wxSize GetLevelSize() const { return mLevelLoader->GetLevelSize(); }

	void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

	void SetLevel(int level);
	void Update(double elapsed);
    /**
     * Gets offset value of x
     * @return mXOffset value
     */
	double GetXOffset() const { return mXOffset; }

    /**
     * Gets offset value of y
     * @return mYOffset value
     */
	double GetYOffset() const { return mYOffset; }

    /**
     * Gets scale value
     * @return mScale value
     */
	double GetScale() const { return mScale; }
	void OnLeftDown(wxMouseEvent &event);
	void SetMousePosition(int x, int y);
	void HeadButt();
    void Vomit(char keycode);

	void Accept(ItemVisitor *visitor);
	//std::shared_ptr<Item> FindFood(double x, double y);
	void SpartyEat();

    //void AddBonus() {mScoreboardTimer->UpdateBonus(); }

    //std::shared_ptr<Scoreboard> GetScoreboard() {return mScoreboardTimer; }

	/**
	 * Function that applies the bonus
	 */
    void ApplyBonus() { mScoreboardTimer->UpdateBonus(); }

	/**
	 * Getter for Level loader object
	 * @return
	 */
    std::shared_ptr<LevelLoader> GetLevelLoader() {return mLevelLoader; }

	void Solve();
};

#endif // PROJECT1_ACTIONSUDOKULIB_ACTIONSUDOKU_H
