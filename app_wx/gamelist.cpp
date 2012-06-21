#include "gamelist.hpp"

using namespace TigData;
using namespace wxTigApp;
using namespace TigLib;

void Notifier::notify() { lst->notifyListChange(); }

void GameList::addListener(wxGameListener *p)
{
  listeners.insert(p);
  p->list = this;
}

void GameList::removeListener(wxGameListener *p)
{
  p->list = NULL;
  listeners.erase(p);
}

void GameList::notifyListChange()
{
  std::set<wxGameListener*>::iterator it;
  for(it = listeners.begin(); it != listeners.end(); it++)
    (*it)->gameListChanged();
}

void GameList::notifyInfoChange()
{
  std::set<wxGameListener*>::iterator it;
  for(it = listeners.begin(); it != listeners.end(); it++)
    (*it)->gameInfoChanged();
}

void GameList::notifyStatusChange()
{
  std::set<wxGameListener*>::iterator it;
  for(it = listeners.begin(); it != listeners.end(); it++)
    (*it)->gameStatusChanged();
}

void GameList::flipReverse() { lister.flipReverse(); }
void GameList::setReverse(bool b) { lister.setReverse(b); }
void GameList::clearTags() { setTags(""); }
void GameList::setTags(const std::string &) {}
void GameList::setSearch(const std::string &str) { lister.setSearch(str); }

bool GameList::sortTitle()
{
  lister.sortTitle();
  return setStat(SS_TITLE);
}
bool GameList::sortDate()
{
  lister.sortDate();
  return setStat(SS_DATE);
}
bool GameList::sortRating()
{
  lister.sortRating();
  return setStat(SS_RATING);
}
bool GameList::sortDownloads()
{
  lister.sortDownloads();
  return setStat(SS_DOWNLOADS);
}

int GameList::size() const { return lister.size(); }

static GameInf &liveToInfo(const LiveInfo &l)
{
  GameInf *gi = (GameInf*)l.extra;
  assert(gi);
  return *gi;
}

wxGameInfo& GameList::edit(int i)
{
  assert(i>=0 && i<size());
  return liveToInfo(lister.get(i));
}