/**
 * @file LevelLoadTest.cpp
 * @author Palina Skakun
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <LevelLoader.h>

TEST(LevelLoader, Construct)
{
	LevelLoader levelLoader;
	ASSERT_EQ(levelLoader.GetDisplayedLevel(),1);
	levelLoader.ChangeLevel(2);
	ASSERT_EQ(levelLoader.GetDisplayedLevel(),2);
	levelLoader.ChangeLevel(0);
	ASSERT_EQ(levelLoader.GetDisplayedLevel(),0);
	levelLoader.ChangeLevel(3);
	ASSERT_EQ(levelLoader.GetDisplayedLevel(),3);

}