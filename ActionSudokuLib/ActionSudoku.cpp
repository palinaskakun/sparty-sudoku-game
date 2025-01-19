/**
 * @file ActionSudoku.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "ActionSudoku.h"
using namespace std;

//Testing Virtual Pixel stuff

/**
 * This is the constructor for the ActionSudoku game setting
 */
ActionSudoku::ActionSudoku()
{
    mScoreboardTimer = std::make_unique<Scoreboard>(this);
    mLevelLoader = make_unique<LevelLoader>();

    // Starts the timer but should probably be somewhere else since it
    //  should appear after the welcome message is gone
    //mScoreboardTimer->Start();
}

/**
 * Draw the game
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the window
 */
void ActionSudoku::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = GetLevelSize().x;
    int pixelHeight = GetLevelSize().y;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    mLevelLoader->OnDraw(graphics);
    mScoreboardTimer->Draw(graphics);

    graphics->PopState();
}

/**
 * Starts the level when called
 * @param level
 */
void ActionSudoku::SetLevel(int level)
{
    mLevelLoader->ChangeLevel(level);

    mScoreboardTimer->ResetTimer();
    mScoreboardTimer->Start(); // Reset the timer whenever a level is selected
}

/**
 * Update the game state by updating the current active level.
 * @param elapsed time elapsed since last update.
 */
void ActionSudoku::Update(double elapsed)
{
    mLevelLoader->Update(elapsed);
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event
 */
void ActionSudoku::OnLeftDown(wxMouseEvent &event)
{
    // Translate these coordinates considering any offsets or scaling
    double translatedX = (mInputMouseX - mXOffset) / mScale;
    double translatedY = (mInputMouseY - mYOffset) / mScale;

    mInputMouseX = translatedX;
    mInputMouseY = translatedY;
    mLevelLoader->GetCurrentLevel()->MoveSpartyTo(mInputMouseX, mInputMouseY);
}

/**
 * Sets the position for mouse
 * @param x
 * @param y
 */
void ActionSudoku::SetMousePosition(int x, int y)
{
    mInputMouseX = x;
    mInputMouseY = y;
}

/**
 * Sparty eating digits
 */
void ActionSudoku::SpartyEat()
{
	mLevelLoader->GetCurrentLevel()->SpartyEat();
}

/**
 * Accept a visitor
 * @param visitor The visitor being accepted
 */
void ActionSudoku::Accept(ItemVisitor *visitor)
{
    mLevelLoader->Accept(visitor);
}

/**
 * Headbutt motion & action for Sparty
 */
void ActionSudoku::HeadButt()
{
    mLevelLoader->GetCurrentLevel()->SpartyHeadButt();
}

/**
 * Passes the level into Vomit function
 * @param keycode
 */
void ActionSudoku::Vomit(char keycode)
{
    mLevelLoader->GetCurrentLevel()->SpartyVomit(keycode);
}
/**
 * Passes level into solve function
 */
void ActionSudoku::Solve()
{
	mLevelLoader->GetCurrentLevel()->Solve();
}