#include <string>
#include <exception>
#include "GameException.h"

GameException::GameException( const char* message )
{
   mMessage = message;
}

GameException::~GameException(void)
throw ()
{
}
