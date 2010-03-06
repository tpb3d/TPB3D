#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

namespace Settings
{
   class SettingsIni
   {
      bool mSettingsAreLoaded;
   protected:
      std::map<std::string, std::string> UserSettings;
//      std::map<std::string, std::string> GlobalSettings;

   public:
      SettingsIni();

      void Load();
      bool SettingsAreLoaded() { return mSettingsAreLoaded; }

      std::string Get(const std::string& Pref);
      int GetInt(const std::string& Pref);
      int Set(std::string Pref, std::string Value);
      int Set(std::string Pref, std::string Value, bool WriteImmediately);
      void ReadIni(std::string FileName, std::map<std::string, std::string>* Settings);
      void SaveIni(std::string FileName, std::map<std::string, std::string>* Settings);
      //extern bool DocumentLoaded;
      //extern std::string CurSettingsPath;
   };
}