#ifndef GUIManager_H
#define GUIManager_H

class EventHandler;
class ObjectBase;
class Park;
class Interface;

class GUIManager : public EventBase
{
private:

   EventHandler& mEVH; // tap the event handler for the app
   Interface& mInterface;

public:
	GUIManager(EventHandler& evh, Interface& rInterface); //, Park* Park);
	~GUIManager();

   bool OnFRCS ();
   bool OnSettings ();
   bool OnTools ();

   bool OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam);
   bool OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam);
   bool OnKeyDown (sf::Key::Code Key);
   bool OnKeyUp (sf::Key::Code Key);
   bool OnMouseMove (Vector2i Scene, Vector2i Cam);
   bool OnMouseWheel (int Delta);
   bool OnResize (Vector2i NewSize);
};

#endif
