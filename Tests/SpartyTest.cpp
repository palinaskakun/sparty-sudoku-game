/**
 * @file SpartyTest.cpp
 * @author Palina Skakun
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Sparty.h>
#include <Level.h>

const std::wstring XML1 = L"levels/level1.xml";

TEST(SpartyTest, Construct)
{
	Level level(XML1);
	Sparty sparty(&level);

	ASSERT_TRUE(sparty.GetLevel() == &level);
}

TEST(SpartyTest, SetPositionTest)
{
	Level level(XML1);
	Sparty sparty(&level);

	double testX = 100;
	double testY = 200;

	// Test SetPosition function
	sparty.SetPosition(testX, testY);
	//ASSERT_EQ(sparty.GetTargetX(), 100);
	//ASSERT_EQ(sparty.GetTargetY(), 200);

}