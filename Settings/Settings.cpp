// Alabama Cajun - Contribution Thanks to;
// Settrings Source Contribution by RFrank.nj, copyright not provided
//
// This will get replaced at some point with a new storage method compatible with the application.
#include "Settings.h"

using namespace Settings;

SettingsIni::SettingsIni()
{
   mSettingsAreLoaded = false;
}

void SettingsIni::Load()
{
   ReadIni("Settings.ini", &UserSettings);
   mSettingsAreLoaded = true;
}
std::string SettingsIni::Get(const std::string& Pref)
{
   if (!mSettingsAreLoaded)
      Load();
   return UserSettings[Pref];
}
int SettingsIni::GetInt(const std::string& Pref)
{
   std::string Value = Get(Pref);
   //std::ostringstream StreamValue;
   //StreamValue << Value;
   int IntValue;
   //StreamValue >> IntValue;
   std::stringstream(Value) >> IntValue;
   return IntValue;
}

int SettingsIni::Set(std::string Pref, std::string Value)
{
   return Set(Pref, Value, false);
}

int SettingsIni::Set(std::string Pref, std::string Value, bool WriteImmediately)
{
   UserSettings[Pref] = Value;
   if (WriteImmediately)
   {
      SaveIni("Settings.ini", &UserSettings);
   }
   return 0;
}

void SettingsIni::SaveIni(std::string FileName, std::map<std::string, std::string>* Settings)
{
   std::cout << "Saving settings...\n";

   std::string CurSection;
   std::string FileContents;
   for ( std::map<std::string,
      std::string>::const_iterator iter = Settings->begin();
      iter != Settings->end(); ++iter)
   {
      std::cout << iter->first << " : " << iter->second << '\n';
      std::string Value = iter->second;
      std::string Section = iter->first;
      size_t DotIndex = Section.find('.');
      if (DotIndex == std::string::npos)
         continue;
      std::string Setting = Section.substr(
         DotIndex+1, Section.length()-DotIndex-1);

      Section = Section.substr(0, DotIndex);
      //std::cout << "Section: " << Section << '\n';
      //std::cout << "\t" << Setting << " : " << Value << '\n';
      if (CurSection != Section) {
         FileContents += "\n[" + Section + "]\n";
         CurSection = Section;
      }
      FileContents += Setting + '=' + Value + '\n';
   }
   //std::cout << FileContents << '\n';
   std::ofstream File (FileName.c_str(), std::ios::trunc);
   if (File.is_open())
   {
      File << FileContents;
   }
   else
   {
      std::cout << "Unable to write settings to " << FileName << '\n';
   }
}

void SettingsIni::ReadIni(std::string FileName, std::map<std::string, std::string>* Settings)
{
   std::ifstream File (FileName.c_str());
   std::string Line;
   std::string Section;
   if (File.is_open())
   {
      while (!File.eof())
      {
         std::getline(File, Line);
         std::cout << Line;
         int Offset = 0;
         while (true)
         {
            if (Line[Offset] == ' ' || Line[Offset] == '\t')
               Offset++;
            else
               break;
         }
         if( Line.size() == 0 || Line[Offset] == ';')
         {
            continue;
         }
         //std::cout << Line;
         // Remove the trailing \r on linux
         if (Line[Line.length()-1] == '\r')
         {
            Line = Line.substr(0, Line.length()-Offset-1);
         }

         if (Line[Offset] == '[' && Line[Line.length()-1] == ']')
         {
            Section = Line.substr(Offset+1, (Line.length()-Offset-2));
            continue;
         }
         size_t EqualOffset = Line.find('=');
         if (EqualOffset == std::string::npos)
            continue;
         std::string Setting = Section + '.' +
            Line.substr(Offset, (EqualOffset-Offset));
         (*Settings)[Setting] = Line.substr(EqualOffset+1, (Line.length()-EqualOffset));
         std::cout << Setting << " : " << (*Settings)[Setting] << '\n';
      }
   }
   else
   {
      std::cout << "Failed to open file " << FileName << "\n";
   }
}
//private:

//   std::string CurSettingsPath = "";

