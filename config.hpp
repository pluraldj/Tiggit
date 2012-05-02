#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <string>
#include <fstream>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include "readjson.hpp"

/* Increase this whenever the cache needs to be updated. This will be
   removed soon, once we apply the upcoming game updater system to the
   cache as well.
 */
#define LAST_CACHE_VERSION 1

struct Config
{
  std::string filename, gamedir;

  // Set true when a forced update is necessary.
  bool updateList, updateTigs, updateCache;

  // Set to true the first time we run only
  bool first_time;

  // Show debug / untested data
  bool debug;

  // True if the user has seen the 'demo' tab message.
  bool seen_demo_msg;

  // True if the user has been asked about where to install games and
  // the program itself
  bool has_asked_dirs;

  int64_t lastTime;

  Config() : updateList(false), updateTigs(false), updateCache(false),
             first_time(false), debug(false), seen_demo_msg(false),
             has_asked_dirs(false),
             lastTime(0x7fffffffffff) {}

  void fail(const std::string &msg)
  {
    throw std::runtime_error(msg);
  }

  // Called when we discover games newer than the current registered
  // time.
  void setLastTime(int64_t newTime)
  {
    if(newTime > lastTime)
      {
        lastTime = newTime;
        write();
      }
  }

  // Called by the install system if this user has been asked about
  // install directories
  void setAskedDirs()
  {
    if(!has_asked_dirs)
      {
        has_asked_dirs = true;
        write();
      }
  }

  void shown_demo_msg()
  {
    if(!seen_demo_msg)
      {
        seen_demo_msg = true;
        write();
      }
  }

  void setGameDir(const std::string &name)
  {
    gamedir = name;
    write();
  }

  void load(const boost::filesystem::path &where)
  {
    using namespace std;

    filename = (where/"config").string();

    bool error = false;

    if(!boost::filesystem::exists(filename))
      {
        error = true;
        first_time = true;
        updateCache = true;
      }
    else
      {
        string repo;
        {
          ifstream f(filename.c_str());
          if(f) f >> repo;
        }

        // Old pre-json config file
        if(repo == "" || repo == "1" || repo == "2")
          // Treat as error
          error = true;

        else
          {
            // Extract json config
            try
              {
                Json::Value root = readJson(filename);

                if(root["repo_version"] != "3")
                  error = true;

                // TODO: We are compiling without 64 bit ints, which
                // is stupid. See if we can fix this before 2038 :)
                // See also in write().

                //lastTime = root["last_time"].asInt64();
                lastTime = root["last_time"].asInt();
                seen_demo_msg = root["seen_demo_msg"].asBool();
                has_asked_dirs = root["has_asked_dirs"].asBool();
                debug = root["debug"].asBool();
                gamedir = root["gamedir"].asString();

                if(gamedir == "")
                  gamedir = "games";

                int cache = root["cache_version"].asInt();
                if(cache < LAST_CACHE_VERSION)
                  updateCache = true;

                if(lastTime < 0) lastTime = 0;
              }
            catch(...)
              {
                // Fail
                error = true;
              }
          }
      }

    if(error)
      {
        updateList = true;
        //updateTigs = true;
      }

    write();
  }

  void write()
  {
    Json::Value root;
    root["repo_version"] = "3";
    // TODO: Subject to 2038-bug
    root["last_time"] = (int)lastTime;
    root["seen_demo_msg"] = seen_demo_msg;
    root["has_asked_dirs"] = has_asked_dirs;
    root["cache_version"] = 1;
    root["debug"] = debug;
    root["gamedir"] = gamedir;

    writeJson(filename, root);
  }
};

Config conf;
#endif
