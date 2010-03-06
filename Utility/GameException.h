#pragma once
#ifndef _GameException_H
#define _GameException_H

using namespace std;

class GameException :
         public std::exception
{
   std::string mMessage;
public:
   GameException( const char* message );
   ~GameException (void) throw ();

   string& get_Message()
   {
      return mMessage;
   }
};

#endif //_GameException_H
