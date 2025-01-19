/**
 * @file Level.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "Level.h"
#include "Item.h"
#include "ItemGiven.h"
#include "ItemBackground.h"
#include "ItemDigit.h"
#include "ItemXray.h"
#include "Sparty.h"
#include "Container.h"
#include <iostream>
#include "Visitors/SpartyFinder.h"
#include "Visitors/ContainerFinder.h"
#include "Visitors/ItemDigitFinder.h"
#include "Visitors/ItemGivenFinder.h"
#include "ItemCandy.h"

using namespace std;

/// Sparty head filename
const wstring SpartyHeadImageName = L"images/sparty-1.png";

/// Sparty Jaw filename
const wstring SpartyJawImageName = L"images/sparty-2.png";

///9x9 Matrix dimension
const int GridOfMatrix = 9;

/**
 * Constructor
 * @param filename Path to the XML file
 */
Level::Level(const std::wstring &filename) : mSolutionMatrix(9, std::vector<int>(9, 0))
{
	Load(filename);

	mGameSize.x = mWidth * mTileWidth;
	mGameSize.y = mHeight * mTileHeight;
}

/**
 * Loads a specified XML file into the level
 * @param filename The location of the XML file on disk
 */
void Level::Load(const std::wstring &filename)
{
	wxXmlDocument xmlDoc;
	if (!xmlDoc.Load(filename))
	{
		wxMessageBox(L"Unable to load Level file");
		return;
	}

	// Get the XML document root node
	auto root = xmlDoc.GetRoot();
	root->GetAttribute(L"width").ToInt(&mWidth);
	root->GetAttribute(L"height").ToInt(&mHeight);
	root->GetAttribute(L"tileheight").ToInt(&mTileHeight);
	root->GetAttribute(L"tilewidth").ToInt(&mTileWidth);

	// Variable to pass to the function
	bool decl = true;

	//
	// Traverse the children of the root
	// node of the XML document in memory
	//
	// Traverse the declarations tag first

	auto child = root->GetChildren();		// Children of root are decs, game, and items
	auto grandChild = child->GetChildren(); // Grandchild of declarations is <given>
	for (; grandChild; grandChild = grandChild->GetNext())
	{
		XmlItem(grandChild, decl, false);
	}

	// Switch to False and go through other tags
	decl = false;

	child = child->GetNext(); // Skip <game> for now bc don't know how to handle
	XmlGame(child);
	auto solutionData = child->GetNodeContent();

	MakeMatrix(solutionData);

	child = child->GetNext(); // At items tag now
	grandChild = child->GetChildren();
	for (; grandChild; grandChild = grandChild->GetNext())
	{
		if (grandChild->GetName() == L"container")
		{
            XmlItem(grandChild, decl, false);

			//Commented out for now so the sparty doesn't eat these digits while they are in container
			//Need to figure out how to store them in Container in a list and draw them there

			// This is saving digits that are inside the containers
			auto grandGrandChild = grandChild->GetChildren();
			for (; grandGrandChild; grandGrandChild = grandGrandChild->GetNext())
			{
				XmlItem(grandGrandChild, decl, true);
			}
		}
		else
		{
			XmlItem(grandChild, decl, false);
		}
	}
}

/**
 *
 * @param node
 * @param declaration
 * @param isInContainer
 */
void Level::XmlItem(wxXmlNode *node, bool declaration, bool isInContainer)
{
	// A pointer for the item we are loading
	shared_ptr<Item> item;

	auto type = node->GetName();
	if (type == L"given")
	{
		item = make_shared<ItemGiven>(this);
	}
	else if (type == L"digit")
	{
		item = make_shared<ItemDigit>(this);
	}
	else if (type == L"background")
	{
		item = make_shared<ItemBackground>(this);
	}
	else if (type == L"container")
	{
		item = make_shared<Container>(this);
    }
	else if (type == L"xray")
	{
		item = make_shared<ItemXray>(this);
	}
	else if (type == L"sparty")
	{
		item = make_shared<Sparty>(this);
	}
    else if (type == L"candy")
    {
        item = make_shared<ItemCandy>(this);
    }

	if (item != nullptr)
	{
		item->XmlLoad(node);
		//current items id
		auto id = item->GetId();
		if (declaration)
		{
			mIdItemMap[id] = item;
		}
		else
		{
			// Handling the Xray capacity, adding the value to the item
			// from its declaration

			if (type == L"xray")
			{
				auto capacity = mIdItemMap[id]->GetXrayCapacity();
				item->SetXrayCapacity(capacity);
			}

			if (type == L"sparty")
			{
				auto targetOffsetX = mIdItemMap[id]->GetTargetOffset().x;
				auto targetOffsetY = mIdItemMap[id]->GetTargetOffset().y;
				item->SetTargetOffset(targetOffsetX,targetOffsetY);
			}

            ItemDigitFinder digitFinder;
            item->Accept(&digitFinder);
            ItemDigit* itemDigit = digitFinder.GetItemDigit();
            if(isInContainer && (itemDigit != nullptr))
            {
                Container* container = getContainerToBeIn();
                container->HoldDigit(itemDigit);
            }

            ItemDigitFinder digitFinderInIdMap;
            mIdItemMap[id]->Accept(&digitFinderInIdMap);
            ItemDigit* itemDigitInIdMap = digitFinderInIdMap.GetItemDigit();

            if(itemDigit != nullptr && itemDigitInIdMap != nullptr) {
                itemDigit->SetValue(itemDigitInIdMap->GetValue());
            }

			mItems.push_back(item);
        }
	}
}

void Level::XmlGame(wxXmlNode *node)
{
	node->GetAttribute(L"col").ToInt(&mSolCol);
	node->GetAttribute(L"row").ToInt(&mSolRow);
}

Container* Level::getContainerToBeIn() {
    ContainerFinder cVisitor;
    for(int i = mItems.size() - 1; i >= 0; i--) {
        auto ptr = mItems[i];
        ptr -> Accept(&cVisitor);
        Container *container = cVisitor.GetContainer();
        if(container != nullptr) {
            return container;
        }
    }
    return nullptr;
}

/**
 * Handles drawing the items from the level on ActionSudokuView
 * @param graphics The wxGraphicsContext object to write to
 */
void Level::OnDraw(shared_ptr<wxGraphicsContext> graphics)
{
    for (auto item : mItems)
    {
        auto id = item->GetId();
        auto dec = mIdItemMap[id];
        int width = dec->GetItemWidth();
        int height = dec->GetItemHeight();

        auto image = dec->GetBitmap();
        auto image2 = dec->GetBitmap2();

		double col = item->GetCol();
		double row = item->GetRow();

        SpartyFinder spartyVisitor;
        mIdItemMap[id] -> Accept(&spartyVisitor);
        Sparty* spartyDescroption = spartyVisitor.GetSparty();
        if(spartyDescroption != nullptr) {
            item -> Accept(&spartyVisitor);
            Sparty* spartyItem = spartyVisitor.GetSparty();
            spartyItem->SetHeadPivot(spartyDescroption->GetHeadPivot());
        }

        item->Draw(graphics, width, height, image, image2, col, row);
	}
}

/**
 * updates location of sparty item
 * @param x the new x location
 * @param y the new y location
 */
void Level::MoveSpartyTo(double x, double y)
{
	SpartyFinder visitor;
	for (auto itemPtr : mItems)
	{
		itemPtr->Accept(&visitor);
		Sparty *sparty = visitor.GetSparty();
		if (sparty != nullptr)
		{
			sparty->SetPosition(x, y);
		}
	}
}

/**
 * Gets Sparty and calls headbutt animation function
 */
void Level::SpartyHeadButt()
{
	SpartyFinder visitor;
	ContainerFinder cVisitor;
	for (auto itemPtr : mItems)
	{
		itemPtr->Accept(&visitor);
		Sparty *sparty = visitor.GetSparty();
		if (sparty != nullptr)
		{
			sparty->HeadButt();
            for (auto ptr: mItems)
            {
                ptr -> Accept(&cVisitor);
                Container *container = cVisitor.GetContainer();

                if(container != nullptr) {
                    if(container->GetCurrentX() <= sparty->GetCurrentX() && sparty->GetCurrentX() <= (container->GetCurrentX() + container->GetCurrentX())
                       && container->GetCurrentY() <= sparty->GetCurrentY() && sparty->GetCurrentY() <= (container->GetCurrentY() + container->GetCurrentY()))
                    {
                        for(int i = 0; i < container->GetHoldingDigits().size(); i++)
                        {
                            container->GetHoldingDigits()[i]->Pop();
                        }
                    }
                }
            }
		}
	}
}

Sparty* Level::GetSpartyInItems() {
    for(auto ptr: mItems)
    {
        SpartyFinder spartyFinder;
        ptr->Accept(&spartyFinder);
        Sparty *sparty = spartyFinder.GetSparty();
        if(sparty != nullptr) {
            return sparty;
        }
    }
    return nullptr;
}

void Level::SpartyVomit(char keycode)
{
    SpartyFinder xrayFinder;

    for(auto ptr: mItems)
    {
        ptr->Accept(&xrayFinder);
        ItemXray* xray = xrayFinder.GetXray();
        Sparty* sparty = GetSpartyInItems();
        if(xray != nullptr && sparty != nullptr)
        {
            int c = (int)(sparty->GetCurrentX() / sparty->GetItemWidth() * 2);
            int r = (int)(sparty->GetCurrentY() / sparty->GetItemHeight() * 2);
            if (xray->RemoveNumber(keycode - '0', r, c))
            {

                break;
            }
        }
    }
}

/**
 * Gets Sparty and calls eating (moving mouth) animation.
 */
void Level::SpartyEat()
{
	SpartyFinder visitor;
	for (auto itemPtr : mItems)
	{
		itemPtr->Accept(&visitor);
		Sparty *sparty = visitor.GetSparty();
		if (sparty != nullptr)
		{
			sparty->Eat();
		}
	}
}

/**
 * Makes a 9x9 matrix out of numbers given for solution.
 * @param data the string of numbers.
 */
void Level::MakeMatrix(const wxString &data)
{
	wxString remaining = data;
	std::vector<int> numbers;

	while (!remaining.IsEmpty())
	{
		wxString token = remaining.BeforeFirst(' ');
		remaining = remaining.AfterFirst(' ');
		numbers.push_back(wxAtoi(token));
	}

	int count = 0;
	for (int i = 0; i < GridOfMatrix; ++i)
	{
		for (int j = 0; j < GridOfMatrix; ++j)
		{
			mSolutionMatrix[i][j] = numbers[count];
			count++;
		}
	}
}

/**
 * checks if game board cell matches the solution cell for game
 * @param row the row position of cell
 * @param col the col position of cell
 * @param item the item to check in cell
 * @return true if matches else false
 */
bool Level::CellMatchesSolution(int row, int col, Item *item)
{

	return mSolutionMatrix[row][col] == item->GetValue();
}

/**
 * Solve function to solve the gameboard.
 */
void Level::Solve()
{
	ItemDigitFinder visitor;
	ItemGivenFinder givenVisitor;
	// Where the game solution starts (col,row)
	auto defaultCol = mSolCol;
	auto defaultRow = mSolRow;
	// Iterator to go through mItems
	auto itemIter = mItems.begin(); // Initialize an iterator for mItems

	//Enter row
	for (int row = 0; row < GridOfMatrix; row++)
	{
		//Enter row and update the Iterator to start from the beginning since we need to check
		//the whole list every time
		itemIter = mItems.begin();
		for(int col = 0; col < GridOfMatrix; col++)
		{
			//itemIter = mItems.begin();

			//Current number in the matrix. We're looking for its representation (digit or given)
			int currNumber = mSolutionMatrix[row][col];


			itemIter = mItems.begin();
			while(itemIter != mItems.end())
			{
				(*itemIter)->Accept(&visitor);
				ItemDigit *digit = visitor.GetItemDigit();
				(*itemIter)->Accept(&givenVisitor);
				ItemGiven *given = givenVisitor.GetItemGiven();

				if(digit != nullptr || given != nullptr)
				{
					if (digit != nullptr)
					{
						auto digitId = digit->GetId();

                        auto colLowerBound = mSolCol;
                        auto colUpperBound = mSolCol + GridOfMatrix;
                        auto rowLowerBound = mSolRow;
                        auto rowUpperBound = mSolRow + GridOfMatrix;
//						if(mIdItemMap[digitId]->GetValue() == currNumber && digit->GetCol() > colUpperBound
//							&& digit->GetCol() < colLowerBound && digit -> GetRow() > rowUpperBound
//							&& digit-> GetRow() < rowLowerBound)

                        if((mIdItemMap[digitId]->GetValue() == currNumber)
                        && (digit -> GetRow() > rowUpperBound || digit-> GetRow() < rowLowerBound))
						{
							digit->SetPosition(defaultCol + col, defaultRow + row);
							break;
						}
					}
					if(given != nullptr && given->GetCol() == col + defaultCol && given->GetRow() == row + defaultRow)
					{
						break;
					}
				}
				++itemIter;
			}

		}
	}
	ResetXray();
}
/**
 * Resets Xray.
 */
void Level::ResetXray()
{
	SpartyFinder xrayFinder;

	for(auto ptr : mItems)
	{
		ptr->Accept(&xrayFinder);
		ItemXray *xray = xrayFinder.GetXray();
		if (xray != nullptr)
		{
			xray->ResetPosition();
		}
	}
}

/**
 * Sets up a level
 */
void Level::SetLevel()
{
}

/**
 * Resets level.
 */
void Level::ResetLevel()
{
	for (auto item : mItems)
	{
		item->ResetPosition();
	}
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Level::Update(double elapsed)
{
	for (auto item : mItems)
	{
		item->Update(elapsed);
	}
}

/**
 * Accepts a visitor into the level to visit each item.
 * @param visitor visitor to accept
 */
void Level::Accept(ItemVisitor *visitor)
{
	for (auto item : mItems)
	{
		item->Accept(visitor);
	}
}

/**
 * Removes an item from the playing area
 * @param item item to remove
 */
void Level::Remove(std::shared_ptr<Item> item)
{
    auto loc = begin(mItems);
    while (loc != end(mItems))
    {
        if(*loc == item)
        {
            mItems.erase(loc);
            break;
        }
        loc++;
    }
}

/**
 * adds an item from the playing area
 * @param item item to add
 */
void Level::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Destructor.
 */
Level::~Level()
{
//    // iterate through all items in the collection
//    for (auto item: mItems)
//    {
//        delete &item;
//    }
//
//    mItems.clear();
}