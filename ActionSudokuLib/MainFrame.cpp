/**
 * @file MainFrame.cpp
 * @author Team Syceus
 */

#include "pch.h"
#include "MainFrame.h"
#include "ActionSudokuView.h"
#include "ids.h"
#include <wx/event.h>

///How big is the window (width)
const int ScreenWidth = 1200;
///How big is the window (height)
const int ScreenHeight = 900;

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Action Sudoku",
           wxDefaultPosition, wxSize(ScreenWidth, ScreenHeight)); // x1200 y900

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer(wxVERTICAL);

    // Create the view class object as a child of MainFrame
    mSudokuView = new ActionSudokuView();
    mSudokuView->Initialize(this);

    // Add it to the sizer
    sizer->Add(mSudokuView, 1, wxEXPAND | wxALL);

    SetSizer(sizer);

    // Layout (place) the child windows.
    Layout();

    // Creating the menu bar
    auto menuBar = new wxMenuBar();

    // Creating the menu options
    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    // File menu option
    fileMenu->Append(IDM_SOLVE, L"&Solve", L"Solve this level");
    fileMenu->Append(wxID_EXIT, L"E&xit\tAlt-X", L"Quit this program");

    // Level menu option
    levelMenu->Append(IDM_LEVEL0, L"&Level 0", L"Load level0");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1", L"Load level1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2", L"Load level2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3", L"Load level3");

    // Help menu option
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    // appendings
    menuBar->Append(fileMenu, L"&File");
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");

    // adding status bar
    SetMenuBar(menuBar);
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    // Bind Menu options
    //Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(&MainFrame::OnQuit));

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnClose, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnExit, this);


    //Bind(wxEVT_COMMAND_MENU_SELECTED,&MainFrame::OnQuit,this,wxID_EXIT);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED,
         &MainFrame::OnLevelTapped,
         this,
         IDM_LEVEL0);
    Bind(wxEVT_COMMAND_MENU_SELECTED,
         &MainFrame::OnLevelTapped,
         this,
         IDM_LEVEL1);
    Bind(wxEVT_COMMAND_MENU_SELECTED,
         &MainFrame::OnLevelTapped,
         this,
         IDM_LEVEL2);
    Bind(wxEVT_COMMAND_MENU_SELECTED,
         &MainFrame::OnLevelTapped,
         this,
         IDM_LEVEL3);
    Bind(wxEVT_COMMAND_MENU_SELECTED,
         &MainFrame::OnSolve,
         this,
         IDM_SOLVE);
}

/**
 * Levels menu option handlers
 * @param event that commands changing level in program
 */
void MainFrame::OnLevelTapped(wxCommandEvent &event)
{
    mSudokuView->OnLevelLoad(event);
}

/**
 * Exit menu option handlers
 * @param event that commands quit program through File->Exit
 */
void MainFrame::OnClose(wxCommandEvent& event)
{
    //event.Skip();

    mSudokuView->Stop();

    Destroy();
}

/**
 * Exit event handler
 * @param event that commands quit program through the red X
 */
void MainFrame::OnExit(wxCloseEvent& event)
{
    //event.Skip();

    mSudokuView->Stop();

    Destroy();
}

/**
 * Solve menu option handlers
 * @param event that commands solving of game
 */
void MainFrame::OnSolve(wxCommandEvent& event)
{
	mSudokuView->OnSolve(event);
//    //shared_ptr<Item> item;
//    for (const auto& level : mLevel) {    // for each Level in mLevels
//         // for each Item in mItems
//            level->Solve();            // call the Solve method on the Level
//    }
}

/**
 * About menu option handlers
 * @param event command to que info pop up
 */
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(L"Action Sudoku",
                 L"Action Sudoku by Team Syceus",
                 wxOK,
                 this);
}