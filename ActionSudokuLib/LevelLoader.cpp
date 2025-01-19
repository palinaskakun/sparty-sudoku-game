/**
 * @file LevelLoader.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "LevelLoader.h"
#include <sstream>

using namespace std;

/// XML0's file path
const wstring XML0 = L"levels/level0.xml";

/// XML1's file path
const wstring XML1 = L"levels/level1.xml";

/// XML2's file path
const wstring XML2 = L"levels/level2.xml";

/// XML3's file path
const wstring XML3 = L"levels/level3.xml";

/// The first playing level
const int startingLevel = 1;

/// Time the level message displays
const int LevelMessageTime = 3;

///Font size for the level message
const int MessageFontSize = 90;

///Font size for the level instructions
const int InstructionsFontSize = 50;

/**
 * Constructor
 */
LevelLoader::LevelLoader()
{
	Load(XML0);
	Load(XML1);
	Load(XML2);
	Load(XML3);
	ChangeLevel(startingLevel);
}

/**
 * Loads a Level XML file into the game
 * @param filename Path of the file
 */
void LevelLoader::Load(const wstring& filename)
{
	auto level = make_shared<Level>(filename);
	mLevels.push_back(level);
}

/**
 * Updates the level displayed to the one passed in
 *
 * This function also gets called when using the menu options
 * @param changedLevel The index of the level to play
 */
void LevelLoader::ChangeLevel(int changedLevel)
{
	auto currentLevel = GetCurrentLevel();
	currentLevel->ResetLevel();
	mDisplayedLevel = changedLevel;
	currentLevel->SetLevel();

	mState = State::Start;
	//unsure
	mLevelMessageTime = 0;

}

/**
 *
 * @param graphics The wxGraphicsContext pointer
 */
void LevelLoader::OnDraw(shared_ptr<wxGraphicsContext> graphics)
{
	GetCurrentLevel()->OnDraw(graphics);
	if (mState == State::Start)
	{
		OnBeginDraw(graphics);
	}
//    else if (mState == State::Play && )
//    {
//        OnFull(graphics);
//    }

    else if (mState == State::Full) // if full & spacebar pressed
    {
        OnFull(graphics);
    }
	else if (mState == State::End)
	{
		OnEndDraw(graphics);
	}
}

/**
 * Handle updates for animation and level state
 * @param elapsed The time since the last update
 */
void LevelLoader::Update(double elapsed)
{
	switch(mState)
	{
		case State::Start: mLevelMessageTime += elapsed;
			if(mLevelMessageTime >= LevelMessageTime)
			{
				mState = State::Play;
				mLevelMessageTime = 0;

			}
			break;

		case State::Play: GetCurrentLevel()->Update(elapsed);
			// some ifs to determine the win lose state
            if(mFull)
            {
                mState = State::Full;
            }
			break;

		case State::Full: mFull=false;


			mFullMessageY -= elapsed * 0.5;  // Adjust the multiplier for desired speed
			if(mFullMessageY <= 0) // When the message reaches the top
			{
				// Transition to another state or hide the message
				mState = State::Play;  // Example transition
                mFullMessageY = 1;
			}
			break;

		case State::End:
			break;
	}
}

/**
 * Draw the level begin message
 * @param graphics The graphics context to draw on
 */
void LevelLoader::OnBeginDraw(shared_ptr<wxGraphicsContext> graphics)
{
	ostringstream message;
	message << "Level " << mDisplayedLevel <<  " Begin";
	DrawMessage(graphics, message.str());

	string instructions = "space: Eat";
	DrawInstructions(graphics, instructions, 1);

	instructions = "0-8: Regurgitate";
	DrawInstructions(graphics, instructions, 2);

	instructions = "B: Headbutt";
	DrawInstructions(graphics, instructions, 3);
}

/**
 * Draw the level begin message
 * @param graphics The graphics context to draw on
 */
void LevelLoader::OnFull(shared_ptr<wxGraphicsContext> graphics)
{
	//mState=State::Full;
	ostringstream messageStream;
	messageStream << "I'm Full!";
	string message = messageStream.str();

	int screenWidth = mLevels[mDisplayedLevel]->GetLevelSize().x;
	int screenHeight = mLevels[mDisplayedLevel]->GetLevelSize().y;

	// Choose a font size proportional to the screen height
	int fontSize = int(screenHeight * 0.05); // Roughly 5% of screen height
	wxFont font(wxSize(0, fontSize),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_BOLD);
	graphics->SetFont(font, *wxRED);

	double messageWidth, messageHeight;
	graphics->GetTextExtent(message, &messageWidth, &messageHeight);

	double messageX = (screenWidth - messageWidth) / 2;
	double messageY = screenHeight * mFullMessageY;

	// Rectangle dimensions
	int rectPadding = 15;  // Adjust this value for more or less padding around the message
	double rectX = messageX - rectPadding;
	double rectY = messageY - rectPadding;
	double rectWidth = messageWidth + 2 * rectPadding;
	double rectHeight = messageHeight + 2 * rectPadding;

	// Draw rectangle
	graphics->SetBrush(*wxWHITE_BRUSH);
	graphics->SetPen(*wxBLACK_PEN);
	graphics->DrawRectangle(rectX, rectY, rectWidth, rectHeight);

	// Draw the message
	graphics->DrawText(message, messageX, messageY);


}

/**
 * Draw the level end message depending on the win state
 * @param graphics The graphics context to draw on
 */
void LevelLoader::OnEndDraw(shared_ptr<wxGraphicsContext> graphics)
{

}

/**
 * Draw a specific level message on the screen
 * @param graphics The graphics context to draw on
 * @param message The message to draw
 */
void LevelLoader::DrawMessage(shared_ptr<wxGraphicsContext> graphics, string message)
{
	graphics->PushState();

	int screenWidth = mLevels[mDisplayedLevel]->GetLevelSize().x;
	int screenHeight = mLevels[mDisplayedLevel]->GetLevelSize().y;

	wxFont bigFont(wxSize(0, 0.1*screenHeight),
				   wxFONTFAMILY_SWISS,
				   wxFONTSTYLE_NORMAL,
				   wxFONTWEIGHT_BOLD);
	graphics->SetFont(bigFont, *wxGREEN);
	//
	// Draw a filled rectangle
	//
	wxBrush rectBrush(*wxWHITE);
	graphics->SetBrush(rectBrush);
	graphics->SetPen(*wxBLACK_PEN);

	int rectWidth = screenWidth*0.6;
	int rectHeight = screenHeight*0.5;

	graphics->DrawRectangle(screenWidth/2-rectWidth/2, screenHeight/2-rectHeight/2, rectWidth, rectHeight);

	// Get width and height of message to center it
	double messageWidth;
	double messageHeight;
	graphics->GetTextExtent(message, &messageWidth, &messageHeight);

	graphics->DrawText(message, screenWidth/2 - messageWidth/2, screenHeight/3);
	graphics->PopState();
}

/**
 * the instructions for drawing the level
 * @param graphics the graphics context to draw on
 * @param message the message to draw
 * @param line the line applicable to?
 */
void LevelLoader::DrawInstructions(shared_ptr<wxGraphicsContext> graphics, string message,
								   int line)
{
	graphics->PushState();

	int screenWidth = mLevels[mDisplayedLevel]->GetLevelSize().x;
	int screenHeight = mLevels[mDisplayedLevel]->GetLevelSize().y;
	//
	// Draw some text
	//
	wxFont font(wxSize(0, 0.05*screenHeight),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_BOLD);
	graphics->SetFont(font, wxColour(*wxBLACK));

	double wid, hit, y;
	graphics->GetTextExtent(message, &wid, &hit);
	if (line == 1)
	{
		y = screenHeight/2;
	}
	else if (line == 2)
	{
		y = screenHeight/2+hit;
	}
	else
	{
		y = screenHeight/2+hit*2;
	}
	graphics->DrawText(message, screenWidth/2 - wid/2, y);
}

/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
void LevelLoader::Accept(ItemVisitor *visitor)
{
    GetCurrentLevel()->Accept(visitor);

    //??????
    //VisitLevelLoader(this);
}