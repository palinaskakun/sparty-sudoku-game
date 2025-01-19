/**
 * @file Scoreboard.h
 * @author Team Syceus
 *
 * Class to represent the Scoreboard
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_SCOREBOARD_H
#define PROJECT1_ACTIONSUDOKULIB_SCOREBOARD_H

#include <wx/graphics.h>
#include <memory>
#include <chrono>

class ActionSudoku;

/**
 * Class to represent the Scoreboard
 *
 * Displays the elapsed time since the game started.
 */
class Scoreboard
{
private:
    /// The game this Scoreboard belongs to
    ActionSudoku *mGame;

    /// Start time of the game
    std::chrono::steady_clock::time_point mStartTime;

    /// indication of if something should be visibe
    bool shouldAppear = false;

    /// Calculating delay time from message display
    std::chrono::steady_clock::duration mDelayTime = std::chrono::seconds(3);

    /// bonus tracker
    int mBonus = 0;
public:
    /// game in which scoreboard exists
    Scoreboard(ActionSudoku *game);

    /// function to initialize game
    void Start(); // Call this after the 3-second welcome message.

    void ResetTimer();

    /// keep track of time
    wxString GetElapsedTime(); // Format: "mm:ss"

    /// to draw scoreboard
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /// updates bonus candy feature
    void UpdateBonus() { mBonus++; }

};

#endif //PROJECT1_ACTIONSUDOKULIB_SCOREBOARD_H