#pragma once
#ifndef _EPDException_H
#define _EPDException_H

using namespace std;

class EPDException :
         public std::exception
{
   std::string mMessage;
public:
   EPDException( const char* message );
   ~EPDException (void) throw ();

   string& get_Message()
   {
      return mMessage;
   }
};

#endif //_EPDException_H
