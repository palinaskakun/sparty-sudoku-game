/**
 * @file ItemPumpkinTest.cpp
 * @author pp
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Container.h>
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

TEST(ItemPumpkinTest, XmlLoad) {
    // Create a mock XML node for testing
    wxXmlNode mockNode(wxXML_ELEMENT_NODE, "Pumpkin");
	LevelMock level(XML1);
    // Add some test attributes
    mockNode.AddAttribute("id", "test");
    mockNode.AddAttribute("image", "pumpkin.png");
    mockNode.AddAttribute("front", "pumpkin-front.png");
    mockNode.AddAttribute("row", "3.75");
    mockNode.AddAttribute("width", "50");

    // Call XmlLoad function
    Container pumpkin(&level);
    pumpkin.XmlLoad(&mockNode);

    // Check if member variables are set correctly
    ASSERT_EQ(pumpkin.GetId(), "test");
    ASSERT_EQ(pumpkin.GetImageFile(), "pumpkin.png");
    ASSERT_EQ(pumpkin.GetFrontImageFile(), "pumpkin-front.png");
    ASSERT_EQ(pumpkin.GetWid(), 50);
    ASSERT_EQ(pumpkin.GetRow(), 3.75);


}