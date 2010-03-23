#pragma once
#include <string>

using namespace std;

class GameException :
         public std::exception
{
   std::string mMessage;
public:
   GameException( const char* message );
   ~GameException (void) throw ();

   const char* get_Message()
   {
      return mMessage.c_str();
   }
};

