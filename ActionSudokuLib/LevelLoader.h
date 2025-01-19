/**
 * @file LevelLoader.h
 * @author Team Syceus
 *
 * Class managing different levels
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_LEVELLOADER_H
#define PROJECT1_ACTIONSUDOKULIB_LEVELLOADER_H

#include "Level.h"

class ActionSudoku;

/**
 * Manages level
 */
class LevelLoader
{
private:

    /// Collection of levels.
    std::vector<std::shared_ptr<Level>> mLevels;

    /// The index of the currently displayed level.
    int mDisplayedLevel = 0;

    /// The length (time) for the level begin/end message
    double mLevelMessageTime = 0;

    /// sparty full
    bool mFull = false;

    /// The level state possibilities
    enum class State { Start, Play, End, Full };

    /// The current level state
    State mState = State::Start;

    /// y position of the full message
    double mFullMessageY = 1;

public:
    /**
     * set the state of xray to full
     */
    void SetFullState() { mState = State::Full; }

    /**
     * set the x ray to full
     * @param status
     */
    void SetFull(bool status) { mFull = status; }

    LevelLoader();
    void Load(const std::wstring &filename);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);
    void OnBeginDraw(std::shared_ptr<wxGraphicsContext> graphics);
    void OnEndDraw(std::shared_ptr<wxGraphicsContext> graphics);

    void ChangeLevel(int desiredLevel);
    void Update(double elapsed);
    void DrawMessage(std::shared_ptr<wxGraphicsContext> graphics, std::string message);
    void DrawInstructions(std::shared_ptr<wxGraphicsContext> graphics,
                          std::string message, int line);

    /**
     * Returns the currently played/displayed level
     * @return The index of the displayed level
     */
    int GetDisplayedLevel() const { return mDisplayedLevel; }

    /**
       * Returns the vector of levels
      * @return The vector of levels
      */
    std::vector<std::shared_ptr<Level>> GetLevels() const { return mLevels; }

    /**
     * getter for level size of displayed level
     * @return wxSize object to indicate size
     */
    wxSize GetLevelSize() const { return mLevels[mDisplayedLevel]->GetLevelSize(); };

    /**
     * Get current level
     * @return current level being displayed
     */
    std::shared_ptr<Level> GetCurrentLevel() const { return mLevels[mDisplayedLevel]; }

    void Accept(ItemVisitor *visitor);

    void OnFull(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //PROJECT1_ACTIONSUDOKULIB_LEVELLOADER_H