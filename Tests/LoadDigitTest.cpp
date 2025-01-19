/**
 * @file LoadDigitTest.cpp
 * @author Palina Skakun
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <ItemDigit.h>

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

TEST(ItemDigitTest, XmlLoadTest) {
	// Create a mock XML node for testing
	wxXmlNode mockNode(wxXML_ELEMENT_NODE, "digit");

	LevelMock level(XML1);

	// Add some test attributes
	mockNode.AddAttribute("id", "test_id");
	mockNode.AddAttribute("image", "0b.png");
	mockNode.AddAttribute("height", "45");
	mockNode.AddAttribute("width", "45");

	// Call XmlLoad function
	ItemDigit digit(&level);
	digit.XmlLoad(&mockNode);

	// Check if member variables are set correctly
	ASSERT_EQ(digit.GetId(), "test_id");
	ASSERT_EQ(digit.GetImageFile(), "0b.png");
	ASSERT_EQ(digit.GetItemHeight(), 45);

}

TEST(ItemDigitTest, SetLocationTest)
{
	LevelMock level(XML1);
	ItemDigit digit(&level);

	int testX = 10;
	int testY = 20;

	// Test SetPosition fucntion
	digit.SetPosition(testX, testY);
//	ASSERT_EQ(digit.GetTargetX(), 10);
//	ASSERT_EQ(digit.GetTargetY(), 20);
}