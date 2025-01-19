/**
 * @file ActionSudokuView.h
 * @author Team Syceus
 *
 * Class for action sudoku screen view
 */


#ifndef PROJECT1_ACTIONSUDOKULIB_ACTIONSUDOKUVIEW_H
#define PROJECT1_ACTIONSUDOKULIB_ACTIONSUDOKUVIEW_H

#include "ActionSudoku.h"
#include "Level.h"

/**
 * Class for action sudoku screen view
 */
class ActionSudokuView : public wxWindow {
private:
	/// Object that describes the game
	ActionSudoku mActionSudoku;

	/// The last stopwatch time
	double mTime = 0;

	/// The stopwatch used to measure elapsed time.
	wxStopWatch mStopWatch;

    /// The Timer to update the scoreboard every second
    wxTimer mTimer;

    /// The Counter for elapsed seconds
    int mElapsedSeconds=0;

//    ///bool if game is running or not
//    bool mGame=false;

//    /// Size of the scoreboard text in virtual pixels
//    const int ScoreboardTextSize = 64;
//
//    /// Top left corner of the scoreboard in virtual pixels
//    const wxPoint ScoreboardTopLeft{10, 10};

    /// to paint command
	void OnPaint(wxPaintEvent& event);

    /// mouse down event
	void OnMouseDown(wxMouseEvent &event);

public:
	ActionSudokuView();
	void Initialize(wxFrame *parent);
	void OnLevelLoad(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
    void OnKeyDown(wxKeyEvent &event);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
	void OnSolve(wxCommandEvent &event);
};

#endif //PROJECT1_ACTIONSUDOKULIB_ACTIONSUDOKUVIEW_H
