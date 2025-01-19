/**
 * @file ItemPumpkinTest.cpp
 * @author Palina Skakun
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <ItemBackground.h>
#include <Level.h>

using namespace std;

const wstring XML1 = L"levels/level1.xml";

const wstring XML2 = L"levels/level2.xml";

const wstring XML3 = L"levels/level3.xml";

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

TEST(ItemBackgroundTest, Construct)
{
Level level(L"levels/level1.xml");
ItemBackground background(&level);

ASSERT_TRUE(background.GetLevel() == &level);
}

TEST(ItemBackgroundTest, XmlLoadTest) {
	// Create a mock XML node for testing
	wxXmlNode mockNode(wxXML_ELEMENT_NODE, "background");
	LevelMock level(XML1);

	// Add some test attributes
	mockNode.AddAttribute("id", "test_id");
	mockNode.AddAttribute("image", "background.png");
	mockNode.AddAttribute("height", "45");
	mockNode.AddAttribute("width", "45");

	// Call XmlLoad function
	ItemBackground background(&level);
	background.XmlLoad(&mockNode);

	// Check if member variables are set correctly
	ASSERT_EQ(background.GetId(), "test_id");
	ASSERT_EQ(background.GetImageFile(), "background.png");
	ASSERT_EQ(background.GetItemHeight(), 45);
	ASSERT_EQ(background.GetItemWidth(), 45);
}

