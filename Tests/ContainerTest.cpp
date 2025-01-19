/**
 * @file ContainerTest.cpp
 * @author Palina Skakun
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

TEST(ContainerTest, XmlLoadTest) {
	// Create a mock XML node for testing
	wxXmlNode mockNode(wxXML_ELEMENT_NODE, "Container");
	LevelMock level(XML1);
	// Add some test attributes
	mockNode.AddAttribute("id", "test_id");
	mockNode.AddAttribute("image", "pumpkin.png");
	mockNode.AddAttribute("front", "pumpkin-front.png");
	mockNode.AddAttribute("height", "45");


	// Call XmlLoad function
	Container container(&level);
	container.XmlLoad(&mockNode);

	// Check if member variables are set correctly
	ASSERT_EQ(container.GetId(), "test_id");
	ASSERT_EQ(container.GetImageFile(), "pumpkin.png");
	ASSERT_EQ(container.GetFrontImageFile(), "pumpkin-front.png");
	ASSERT_EQ(container.GetHit(), 45);

}

TEST(ContainerTest, SetLocationTest)
{
	LevelMock level(XML1);
	Container container(&level);

	int testX = 30;
	int testY = 50;

	// Test SetPosition fucntion
	container.SetPosition(testX, testY);
	ASSERT_EQ(container.GetX(), 30);
	ASSERT_EQ(container.GetY(), 50);
}