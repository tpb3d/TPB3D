#pragma once
class EventDelegate
{
public:
   EventDelegate(void);
   virtual ~EventDelegate(void);
   virtual void Dispatch (int e) = 0;
};

