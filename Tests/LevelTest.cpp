/**
 * @file LevelTest.cpp
 * @author pp
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <ActionSudoku.h>
#include <ActionSudokuView.h>
#include <ItemCounter.h>
#include <ItemDigit.h>
#include <Item.h>

using namespace std;

const wstring XML1 = L"levels/level1.xml";

const wstring XML2 = L"levels/level2.xml";

const wstring XML3 = L"levels/level3.xml";

/** Mock class for testing the class Level */
class LevelMock : public Level
{
    private:
    std::vector<std::shared_ptr<Item>> mItems;

    public:
        LevelMock(const std::wstring &filename) : Level(filename) {}

        void Add(shared_ptr<Item> item) { mItems.push_back(item);}

};

//construct

TEST(LevelTest, Construct) {
    LevelMock level(XML1);
}

// loading each file
TEST(LevelTest, Load)
{
    //level one by xml

    LevelMock level(XML1);
    ItemCounter counter;
    level.Accept(&counter);

    auto givenCount = counter.GetGivenCount();
    auto xrayCount = counter.GetXrayCount();
    auto spartyCount = counter.GetSpartyCount();
    auto digitCount = counter.GetDigitCount();

    ASSERT_EQ(givenCount, 28);
    ASSERT_EQ(xrayCount, 1);
    ASSERT_EQ(spartyCount, 1);
    ASSERT_EQ(digitCount, 53);

    //level two by xml

    LevelMock level2(XML2);
    ItemCounter counter2;
    level2.Accept(&counter2);

    auto givenCount2 = counter2.GetGivenCount();
    auto xrayCount2 = counter2.GetXrayCount();
    auto spartyCount2 = counter2.GetSpartyCount();
    auto digitCount2 = counter2.GetDigitCount();

    ASSERT_EQ(givenCount2, 34);
    ASSERT_EQ(xrayCount2, 1);
    ASSERT_EQ(spartyCount2, 1);
    ASSERT_EQ(digitCount2, 47);

    //level three by xml

    LevelMock level3(XML3);
    ItemCounter counter3;
    level3.Accept(&counter3);

    auto givenCount3 = counter3.GetGivenCount();
    auto xrayCount3 = counter3.GetXrayCount();
    auto spartyCount3 = counter3.GetSpartyCount();
    auto digitCount3 = counter3.GetDigitCount();

    ASSERT_EQ(givenCount3, 30);
    ASSERT_EQ(xrayCount3, 1);
    ASSERT_EQ(spartyCount3, 1);
    ASSERT_EQ(digitCount3, 51);

}


//TEST(LevelTest, HitTest)
//{
//    LevelMock level4(XML1);
//
//    // creating digit, adding to level, checking position
//    shared_ptr<Item> item = make_shared<Item>(&level4);
//    level4.Add(item);
//    item->SetPosition(100, 200);
////
//    auto x =level4.HitTest(100.0,200.0);
//
////    ASSERT_EQ(level4.HitTest(100, 200), item) <<
////                                                     L"Testing digit at 100, 200";
//}
//

