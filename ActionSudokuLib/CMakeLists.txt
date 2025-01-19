project(ActionSudokuLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h
        ItemCounter.h
        ItemCounter.cpp
        Visitors/ItemVisitor.h
        Visitors/ItemVisitor.cpp ActionSudoku.cpp ActionSudoku.h ActionSudokuView.cpp ActionSudokuView.h ids.h Level.cpp Level.h Item.cpp Item.h LevelLoader.cpp LevelLoader.h
        Sparty.cpp
        Sparty.h ItemDigit.cpp ItemDigit.h ItemGiven.cpp ItemGiven.h ItemBackground.cpp ItemBackground.h ItemXray.cpp ItemXray.h Scoreboard.cpp Scoreboard.h
		Container.cpp Container.h
		Visitors/SpartyFinder.cpp
        Visitors/SpartyFinder.h
        DigitEater.cpp
        DigitEater.h
        Visitors/ContainerFinder.cpp
        Visitors/ContainerFinder.h
        Visitors/ItemDigitFinder.cpp
        Visitors/ItemDigitFinder.h
		ItemCandy.cpp
		ItemCandy.h
		Visitors/ItemGivenFinder.cpp
		Visitors/ItemGivenFinder.h
        Visitors/BonusResetter.cpp
        Visitors/BonusResetter.h
		Visitors/OverlapChecker.cpp
		Visitors/OverlapChecker.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)