/**
 * @file ItemTest.cpp
 * @author Team Syceus
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <Item.h>

using namespace std;

const wstring XML1 = L"levels/level1.xml";

const wstring XML2 = L"levels/level2.xml";

const wstring XML3 = L"levels/level3.xml";

/// Level 0 filename
const std::wstring level0 = L"levels/level0.xml";
/// a given 0 filename
const std::wstring Given0ImageName = L"images/b0.png";

/** Mock class for testing the class Item */
class ItemMock : public Item
{
private:
	Level *mLevel;
    std::string mId;
public:
    ItemMock(Level *level) : Item(level) { mLevel = level; }
};


/** Mock class for testing the class Level */
class LevelMock : public Level
{
private:
	std::vector<std::shared_ptr<Item>> mItems;
	int mTileWidth = 48;
	int mTileHeight = 48;

public:
	LevelMock(const std::wstring &filename) : Level(filename) {}

	void Add(shared_ptr<Item> item) { mItems.push_back(item);}

	int GetTileHeight() const {
		return 10;  // or whatever value you want to use in testing
	}

	int GetTileWidth() const {
		return 10;  // or whatever value you want to use in testing
	}

};

// test item constructor
TEST(ItemTest, Construct) {
    Level level;
    ItemMock item(&level);

	ASSERT_TRUE(item.GetLevel() == &level);
}

TEST(ItemTest, GetId)
{
    // Create a mock XML node for testing
    wxXmlNode mockNode(wxXML_ELEMENT_NODE, "Item");

	LevelMock level(XML1);
    // Add some test attributes
    mockNode.AddAttribute("id", "hi123");

    // Call XmlLoad function
    Item item(&level);
    item.XmlLoad(&mockNode);

    auto recieved_id = item.GetId();

    // Check if member variables are set correctly
    ASSERT_EQ(recieved_id, "hi123");
}


TEST(ItemTest, GetCol)
{
    // Create a mock XML node for testing
    wxXmlNode mockNode(wxXML_ELEMENT_NODE, "Item");

	LevelMock level(XML1);
    // Add some test attributes
    mockNode.AddAttribute("col", "1.2345");

    // Call XmlLoad function
    Item item(&level);
    item.XmlLoad(&mockNode);

    auto recieved_col = item.GetCol();

    // Check if member variables are set correctly
    ASSERT_EQ(recieved_col, 1.2345);
}

TEST(ItemTest, GetRow)
{
    // Create a mock XML node for testing
    wxXmlNode mockNode(wxXML_ELEMENT_NODE, "Item");

    // Add some test attributes
    mockNode.AddAttribute("row", "9.876");

	LevelMock level(XML1);
    // Call XmlLoad function
    Item item(&level);
    item.XmlLoad(&mockNode);

    auto recieved_row = item.GetRow();

    // Check if member variables are set correctly
    ASSERT_EQ(recieved_row, 9.876);
}

TEST(ItemTest, GetWid)
{
    // Create a mock XML node for testing
    wxXmlNode mockNode(wxXML_ELEMENT_NODE, "Item");

	LevelMock level(XML1);
    // Add some test attributes
    mockNode.AddAttribute("width", "88");

    // Call XmlLoad function
    Item item(&level);
    item.XmlLoad(&mockNode);

    auto recieved_wid = item.GetItemWidth();

    // Check if member variables are set correctly
    ASSERT_EQ(recieved_wid, 88);
}

TEST(ItemTest, GetHit)
{
    // Create a mock XML node for testing
    wxXmlNode mockNode(wxXML_ELEMENT_NODE, "Item");

	LevelMock level(XML1);
    // Add some test attributes
    mockNode.AddAttribute("height", "99");

    // Call XmlLoad function
    Item item(&level);
    item.XmlLoad(&mockNode);

    auto recieved_hit = item.GetItemHeight();

    // Check if member variables are set correctly
    ASSERT_EQ(recieved_hit, 99);
}

TEST(ItemTest, GetXGetY)
{
	LevelMock level(XML1);
    Item item(&level);
    auto recieved_x = item.GetX();
    auto recieved_y = item.GetY();

    // Check if member variables are assigned/defaulted
    ASSERT_EQ(recieved_x, 0);
    ASSERT_EQ(recieved_y, 0);

    item.SetPosition(34,67);

    recieved_x = item.GetX();
    recieved_y = item.GetY();

    ASSERT_EQ(recieved_x, 34);
    ASSERT_EQ(recieved_y, 67);
}

TEST(ItemTest, SetPosition)
{
	LevelMock level(XML1);
    Item item(&level);

    int testX = 75;
    int testY = 25;

    // Test Set
    item.SetPosition(testX, testY);
    ASSERT_EQ(item.GetX(), 75);
    ASSERT_EQ(item.GetY(), 25);
}

//TEST(ItemTest, HitTest)
//{
//    Item item(nullptr);
//
//    int testX = 125;
//    int testY = 150;
//
//    // Test Set
//    item.SetPosition(testX, testY);
//    ASSERT_TRUE(item.HitTest(125.0,150.0));
//}