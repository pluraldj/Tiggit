#ifndef __WXAPP_GAMEDATA_HPP_
#define __WXAPP_GAMEDATA_HPP_

#include "gamelist.hpp"
#include "tiglib/repo.hpp"
#include "gameconf.hpp"
#include "tiglib/news.hpp"
#include "appupdate.hpp"

namespace wxTigApp
{
  struct GameNews : wxGameNews
  {
    TigLib::NewsReader news;
    std::vector<wxGameNewsItem> items;

    GameNews(TigLib::Repo *repo) : news(repo) {}

    const wxGameNewsItem &get(int i) const { return items[i]; }
    int size() const { return items.size(); }
    void reload();
    void markAsRead(int);
    void markAllAsRead();
  };

  struct GameData : wxGameData
  {
    GameList *latest, *freeware, *demos, *installed;

    GameConf config;
    GameNews news;
    TigLib::Repo &repo;

    wxWindow *frame;

    AppUpdater updater;

    GameData(TigLib::Repo &rep);
    ~GameData();

    wxGameList &getLatest() { return *latest; }
    wxGameList &getFreeware() { return *freeware; }
    wxGameList &getDemos() { return *demos; }
    wxGameList &getInstalled() { return *installed; }

    std::string getRepoDir() { return repo.getPath(); }
    bool moveRepo(const std::string &newPath);

    bool isActive();

    // Notify us that an update is available. This will prompt the
    // user about the appropriate action.
    void updateReady();

    // Load or reload the dataset
    void loadData();

    // User clicked a notification button
    void notifyButton(int id);

    // Deallocate all GameInf structures
    void killData();

    // Called when a game has started or finished installing, or has
    // been uninstalled.
    void installStatusChanged()
    {
      // Notify main lists that their views should be updated
      latest->notifyInfoChange();
      freeware->notifyInfoChange();
      demos->notifyInfoChange();

      // Refresh the installed list.
      installed->lister.refresh();
      installed->notifyListChange();
    }

    // Notify all lists that the main data has been reloaded.
    void notifyReloaded()
    {
      latest->notifyListChange();
      freeware->notifyListChange();
      demos->notifyListChange();
      installed->notifyListChange();
    }

    // Called regularly when there are games being installed, to
    // update display status.
    void updateDisplayStatus()
    {
      latest->notifyStatusChange();
      freeware->notifyStatusChange();
      demos->notifyStatusChange();
      installed->notifyStatusChange();
    }

    wxGameConf &conf() { return config; }
    wxGameNews &getNews() { return news; }
  };
}
#endif
