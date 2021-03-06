#ifndef __GAMETAB_HPP_
#define __GAMETAB_HPP_

#include "tabbase.hpp"
#include "gamelist.hpp"
#include <time.h>

namespace wxTiggit
{
  struct ImageViewer;

  struct GameTab : TabBase, wxGameListener
  {
    GameTab(wxNotebook *parent, const wxString &name, wxGameList &lst);

  protected:
    GameListView *list;
    wxGameList &lister;

  private:
    int select;
    time_t last_launch;

    // Controls
    wxButton *b1, *b2;
    wxTextCtrl *textView, *searchCtrl;
    ImageViewer *screenshot;
    wxListBox *tags;
    wxChoice *rateBox;
    wxStaticText *rateText;
    wxString rateString[7];

    // List of tags shown in the tag view window
    std::vector<std::string> tagList;

    // wxGameListener functions
    void gameInfoChanged();
    void gameSelectionChanged();
    void gameListChanged();
    void gameStatusChanged() {}

    // TabBase functions
    void gotFocus();
    int getTitleNumber();

    // Event handling functions
    void onSpecialKey(wxCommandEvent &event);
    void onUrlEvent(wxTextUrlEvent &event);
    void onRating(wxCommandEvent &event);
    void onTagSelect(wxCommandEvent &event);
    void onSearch(wxCommandEvent &event);
    void onGamePage(wxCommandEvent &event);
    void onButton(wxCommandEvent &event);
    void onListActivate(wxListEvent &event);
    void onListDeselect(wxListEvent &event);
    void onListSelect(wxListEvent &event);
    void onListRightClick(wxListEvent &event);
    void onContextClick(wxCommandEvent &evt);

    // Internal functions
    void updateSelection();
    void updateTags();
    void fixButtons();
    void updateGameInfo();
    void doAction1(int index);
    void doAction2(int index);
  };
}
#endif
