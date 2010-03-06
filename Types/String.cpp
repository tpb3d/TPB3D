#include "String.h"

int ToInt(std::string Other)
{
   std::istringstream s(Other);
   int To;
   s >> To;
   return To;
}
