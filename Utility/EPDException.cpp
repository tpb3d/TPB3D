#include <string>
#include <exception>
#include "EPDException.h"

EPDException::EPDException( const char* message )
{
   mMessage = message;
}

EPDException::~EPDException(void)
throw ()
{
}
