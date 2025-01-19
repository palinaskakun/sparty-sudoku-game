/**
 * @file ActionSudokuView.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "ActionSudokuView.h"
#include "ids.h"
#include "Visitors/SpartyFinder.h"
#include "DigitEater.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/timer.h>

/// Frame duration in milliseconds
const int FrameDuration = 30;

using namespace std;

ActionSudokuView::ActionSudokuView()
{
}

/**
 * Initialize the game view class.
 * @param mainFrame parent window for this class
 */
void ActionSudokuView::Initialize(wxFrame *mainFrame)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Create(mainFrame, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    Bind(wxEVT_PAINT, &ActionSudokuView::OnPaint, this);

    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &ActionSudokuView::OnLevelLoad, this,
                    IDM_LEVEL0);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &ActionSudokuView::OnLevelLoad, this,
                    IDM_LEVEL1);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &ActionSudokuView::OnLevelLoad, this,
                    IDM_LEVEL2);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &ActionSudokuView::OnLevelLoad, this,
                    IDM_LEVEL3);
    mTimer.Bind(wxEVT_TIMER, &ActionSudokuView::OnTimer, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    Bind(wxEVT_TIMER, &ActionSudokuView::OnTimer, this);
    Bind(wxEVT_LEFT_DOWN, &ActionSudokuView::OnMouseDown, this);
    Bind(wxEVT_KEY_DOWN, &ActionSudokuView::OnKeyDown, this);
    mStopWatch.Start();
}

/**
 * handles tracking time in game
 * @param event timer event
 */
void ActionSudokuView::OnTimer(wxTimerEvent &event)
{
    mElapsedSeconds++;
    Refresh(); // This will cause a paint event to be generated
}

/**
 * This functions takes care of the painting events upon draw for the game
 * @param event Paint event
 */
void ActionSudokuView::OnPaint(wxPaintEvent &event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mActionSudoku.Update(elapsed);

    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    /// Tell the game class to draw
    wxRect rect = GetRect();

    mActionSudoku.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

/**
 * Handles Mouse Down Clicks
 * @param event Mouse event
 */
void ActionSudokuView::OnMouseDown(wxMouseEvent &event)
{
    mActionSudoku.SetMousePosition(event.GetX(), event.GetY());
    mActionSudoku.OnLeftDown(event);
}

/**
 *  handler for specific Levels to be set
 * @param event command event
 */
void ActionSudokuView::OnLevelLoad(wxCommandEvent &event)
{

    if (event.GetId() == IDM_LEVEL0)
    {
        mActionSudoku.SetLevel(0);
    }
    else if (event.GetId() == IDM_LEVEL1)
    {
        mActionSudoku.SetLevel(1);
    }
    else if (event.GetId() == IDM_LEVEL2)
    {
        mActionSudoku.SetLevel(2);
    }
    else if (event.GetId() == IDM_LEVEL3)
    {
        mActionSudoku.SetLevel(3);
    }

    mElapsedSeconds = 0;

    Refresh();
}

/**
 * handler for keyboard inputs
 * @param event key pressed event
 */
void ActionSudokuView::OnKeyDown(wxKeyEvent &event)
{
    auto keycode = event.GetKeyCode();

    if (keycode == 'B')
    {
        mActionSudoku.HeadButt();
    }

    int test_variable = 0;

    if (keycode == WXK_SPACE)
    {

        mActionSudoku.SpartyEat();
        // Space bar was pressed
        SpartyFinder spartyFinder;
        // Getting ptr errors here not sure what to do yet
        mActionSudoku.Accept(&spartyFinder);
        auto sparty = spartyFinder.GetSparty();
        auto xray = spartyFinder.GetXray();
        auto x = sparty->GetCurrentX();
        auto y = sparty->GetCurrentY();

         if (xray->IsFull()) // need to incorp w digit eater checking if next to digit
         {
             auto levelLoader = mActionSudoku.GetLevelLoader();
             levelLoader->SetFull(true);
         }
        //{
        DigitEater eater(x, y, xray->IsFull());
        mActionSudoku.Accept(&eater);

        sparty->Eat(); // this would trigger eating animation by setting the bool attribute true

        eater.Eat(xray);//, mActionSudoku.GetScoreboard());

        if (eater.GotBonus())
        {
            mActionSudoku.ApplyBonus();
        }

        //}

    }

    if ('0' <= keycode && keycode <= '9')
    {
        mActionSudoku.Vomit(keycode);
    }

}

/**
 * Solve menu option handlers
 * @param event that commands solving of game
 */
void ActionSudokuView::OnSolve(wxCommandEvent &event)
{
    mActionSudoku.Solve();
}
