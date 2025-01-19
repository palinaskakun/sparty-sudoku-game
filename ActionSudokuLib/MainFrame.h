/**
 * @file MainFrame.h
 * @author Team Syceus
 *
 * The top-level (main) frame of the application
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_MAINFRAME_H
#define PROJECT1_ACTIONSUDOKULIB_MAINFRAME_H
#include "ActionSudokuView.h"
/**
 * The top-level (main) frame of the application
 */

class MainFrame : public wxFrame {
private:
    /// the action sudoko view
    ActionSudokuView* mSudokuView;
    /// vector of pointers to levels
    std::vector<std::shared_ptr<Level>> mLevel;
    ///vector of pointers to items
    std::vector<std::shared_ptr<Item>> mItems;

    void OnExit(wxCloseEvent& event);
    void OnSolve(wxCommandEvent& event);
    void OnAbout(wxCommandEvent &event);
public:
    void Initialize();
    void OnLevelTapped(wxCommandEvent& event);
    //void OnQuit(wxCommandEvent &event);
    void OnClose(wxCommandEvent &event);
};

#endif //PROJECT1_ACTIONSUDOKULIB_MAINFRAME_H
