/**
 * @file Scoreboard.cpp
 * @author Palina Skakun
 */

#include "pch.h"
#include "Scoreboard.h"
#include "ActionSudoku.h"
#include "Visitors/BonusResetter.h"

using namespace std;

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

/// Top left corner of the scoreboard in virtual pixels
const wxPoint ScoreboardTopLeft = wxPoint(10, 10);

/// White color for the timer
const wxColour TimerColor = wxColour(255, 255, 255);

/// Seconds in a minute
const int SecondsInMinute = 60;

/// bonus time deducted as feature in seconds
const int SpecialFeatureTime = 10;

/**
 * Constructor
 * @param game Game which scoreboard is being implemented in
 */
Scoreboard::Scoreboard(ActionSudoku* game) : mGame(game)
{
    Start();
}

/**
 * Initializes game, starts clock
 */
void Scoreboard::Start()
{
	mStartTime = chrono::steady_clock::now();
}

/**
 * resets clock
 */
void Scoreboard::ResetTimer()
{
    BonusResetter resetter;
    mGame->Accept(&resetter);
    mBonus = 0;
    shouldAppear = false;
}

/**
 * Tracks time during game
 * @return wxString to provide time passed
 */
wxString Scoreboard::GetElapsedTime()
{
    auto now = chrono::steady_clock::now();

    auto elapsed = chrono::duration_cast<chrono::seconds>(now - mStartTime);

    if (elapsed >= mDelayTime && !shouldAppear)
    {
        shouldAppear = true;
        mStartTime = now;
        elapsed = chrono::seconds(0);
    }
    else if(!shouldAppear)
    {
        return wxT("0:00");
    }

    int minutes = elapsed.count() / SecondsInMinute;
    int seconds = elapsed.count() % SecondsInMinute;

    // including bonus feature
    seconds = seconds - (mBonus*SpecialFeatureTime);

    return wxString::Format(wxT("%2d:%02d"), minutes, seconds);
}

/**
 * Draws scoreboard on game window
 * @param graphics pointer to drawing
 */
void Scoreboard::Draw(shared_ptr<wxGraphicsContext> graphics)
{
	wxString timeStr = GetElapsedTime();

    if(shouldAppear)
    {
        graphics->PushState();

	    graphics->Translate(ScoreboardTopLeft.x, ScoreboardTopLeft.y);
	    graphics->Scale(mGame->GetScale(), mGame->GetScale());

	    wxFont timerFont(wxSize(0, ScoreboardTextSize),
	    				 wxFONTFAMILY_SWISS,
	    				 wxFONTSTYLE_NORMAL,
	    				 wxFONTWEIGHT_BOLD);

	    graphics->SetFont(timerFont, TimerColor);
	    graphics->DrawText(timeStr, ScoreboardTopLeft.x, ScoreboardTopLeft.y);

	    graphics->PopState();
    }
}