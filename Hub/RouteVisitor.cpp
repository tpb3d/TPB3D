#include "RouteVisitor.h"

RouteVisitor::RouteVisitor (RoutingRequest& rq, int count)
:  mroutingRequest (rq)
{
   m_Boarding = false;
}

RouteVisitor::~RouteVisitor ()
{
}
