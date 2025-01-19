/**
 * @file ItemXrayTest.cpp
 * @author pp
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <ItemXray.h>

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


TEST(ItemXrayTest, XmlLoad) {
    // Create a mock XML node for testing
    wxXmlNode mockNode(wxXML_ELEMENT_NODE, "Xray");

    // Add some test attributes
    mockNode.AddAttribute("id", "testy_test");
    mockNode.AddAttribute("image", "xray.png");
    mockNode.AddAttribute("col", "2.25");
    mockNode.AddAttribute("capacity", "7");

	LevelMock level(XML1);

    // Call XmlLoad function
    ItemXray xray(&level);
    xray.XmlLoad(&mockNode);

    // Check if member variables are set correctly
    ASSERT_EQ(xray.GetId(), "testy_test");
    ASSERT_EQ(xray.GetImageFile(), "xray.png");
    ASSERT_EQ(xray.GetCol(), 2.25);
    ASSERT_EQ(xray.GetCapacity(), 7);

}