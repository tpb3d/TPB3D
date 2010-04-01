#ifndef GUIManager_H
#define GUIManager_H

#include <CEGUI.h>

#include <RendererModules/OpenGLGUIRenderer/openglrenderer.h>

class EventHandler;
class ObjectBase;
class Park;
class Interface;

class GUIManager : public EventBase
{
private:

	CEGUI::System* mpSystem;
	CEGUI::OpenGLRenderer* mpRenderer;
	CEGUI::WindowManager* mpWM;
	CEGUI::Window* mpRootWind;

	typedef std::map<sf::Key::Code, CEGUI::Key::Scan> KeyMap;
	typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> MouseButtonMap;

	KeyMap mKeyMap;
	MouseButtonMap mMouseButtonMap;
	//bool mPlacingRoom;
	//ObjectBase* mRoom;

   EventHandler& mEVH; // tap the event handler for the app
   Interface& mInterface;

public:
	GUIManager(EventHandler& evh, Interface& rInterface); //, Park* Park);
	~GUIManager();

   bool OnToolHit (const HR_Events tool);
   bool OnPlay (const CEGUI::EventArgs& e);
   bool OnFRCS ();
   bool OnSettings ();
   bool OnTools ();
   bool OnExit (const CEGUI::EventArgs& e);
   bool OnInternet (const CEGUI::EventArgs& e);

   bool OnBuilding (const CEGUI::EventArgs& e);   // concrete until we setup registering the rooms
   bool OnSelect (const CEGUI::EventArgs& e);
   bool OnRemove (const CEGUI::EventArgs& e);

	//bool Initialize(sf::RenderWindow* Win);
   bool OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam);
   bool OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam);
   bool OnKeyDown (sf::Key::Code Key);
   bool OnKeyUp (sf::Key::Code Key);
   bool OnMouseMove (Vector2i Scene, Vector2i Cam);
   bool OnMouseWheel (int Delta);
   bool OnResize (Vector2i NewSize);
	void Draw();
   void Lock();
   void Unlock();

	CEGUI::System* getSystem() { return mpSystem; }
	CEGUI::WindowManager* getWindowManager() { return mpWM; }
	void setRootWindow(CEGUI::Window* Win) {mpSystem->setGUISheet(Win); mpRootWind = Win;}
	CEGUI::Window* LoadLayout(const std::string& Name);
	CEGUI::Window* LoadLayout(const std::string& Name, CEGUI::Window* Parent);

	void InitMaps();
	CEGUI::Key::Scan CEKey(sf::Key::Code Code);
	CEGUI::MouseButton CEMouseButton(sf::Mouse::Button Button);
};

#endif
