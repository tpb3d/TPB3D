// Alabama Cajun - Contribution Thanks to;
// GUIManager Source Contribution SFML (Source Forge example code heavily modified)
// Modificationa by RFrank.nj, AlabamaCajun, Crazy2be copyright 2009.
// Modified for ThemeParkBuilder 3D The Game 2010
//  --------------------------------------------------------------------
//  Licensed according to the GPL v3.0
//
//  GUI Manager Class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#include <SFML/System.hpp>
#include <CEGUI.h>

#include <RendererModules/OpenGLGUIRenderer/openglrenderer.h>
#include <CEGUISystem.h>
#include <CEGUIDefaultResourceProvider.h>
#include <iostream>
#include <string>
#include "../Utility/GameException.h"

#include "../Hub/Event.h"
#include "FRCSWindow.h"
#include "SettingsWindow.h"
#include "ToolsWindow.h"
#include "GUIManager.h"

#define LOOK "WindowsLook"

GUIManager::GUIManager(EventHandler& revh, Interface& rInterface) //, Park* Park) can't pass a Park as there will be more than one. Think events
:  mpRenderer (NULL)
,  mpSystem (NULL)
,  mEVH (revh)
,  mInterface (rInterface)
{
	InitMaps();
	try
	{
	   using namespace CEGUI;
	   // LOOK, we are USING THE CEGUI NAMESPACE!! The extra CEGUI::'s are not nessesary...
		mpRenderer = new OpenGLRenderer(0);
		mpSystem = new System(mpRenderer);
      DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>
         (System::getSingleton().getResourceProvider());

      rp->setResourceGroupDirectory("resource", "data/gui/");
      Imageset::setDefaultResourceGroup("resource");
      Font::setDefaultResourceGroup("resource");
      Scheme::setDefaultResourceGroup("resource");
      WidgetLookManager::setDefaultResourceGroup("resource");
      WindowManager::setDefaultResourceGroup("resource");

		SchemeManager::getSingleton().loadScheme( LOOK ".scheme");
		FontManager::getSingleton().createFont("DejaVuSans-10.font");

		mpWM = WindowManager::getSingletonPtr();

      mpRootWind = mpWM->createWindow( "DefaultWindow", "root" );
      mpSystem->setGUISheet( mpRootWind );

      ImagesetManager::getSingletonPtr()->getImageset(LOOK)->setAutoScalingEnabled(false);

      mpSystem->setDefaultMouseCursor(LOOK, "MouseArrow");
	}
	catch (CEGUI::Exception& e)
	{
      throw new GameException(e.getMessage().c_str());
	}
}

GUIManager::~GUIManager()
{
	delete mpSystem;
	delete mpRenderer;
}

void GUIManager::Lock()
{
   this->mpRenderer->setMutedState(true);
}

void GUIManager::Unlock()
{
   this->mpRenderer->setMutedState(false);
   this->mpRenderer->setDisplaySize(mpRenderer->getSize());
}

CEGUI::Window* GUIManager::LoadLayout(const std::string& Name) {
   return LoadLayout(Name, mpRootWind);
}

CEGUI::Window* GUIManager::LoadLayout(const std::string& Name, CEGUI::Window* Parent) {
   CEGUI::Window* pLayout = mpWM->loadWindowLayout(Name);
   Parent->addChildWindow(pLayout);
   return pLayout;
}

void GUIManager::Draw()
{
	mpSystem->renderGUI();
}

static FRCSWindow frcswin;
static SettingsWindow* setwin = NULL;
static ToolsWindow ToolsWin;

/* Handling events... */
bool GUIManager::OnPlay (const CEGUI::EventArgs& e)
{
   return true;
}

bool GUIManager::OnToolHit (const HR_Events tool)
{
   switch (tool)
   {
   case HR_Settings:
      return OnSettings();
   case HR_Tools:
      return OnTools();
   }
   return false;
}

bool GUIManager::OnTools ()
{
   ToolsWin.Create (this->mpRootWind);
   return true;
}

bool GUIManager::OnSettings ()
{
   if (setwin == NULL)
   {
      setwin = new SettingsWindow (mInterface);
   }
   setwin->Create (this->mpRootWind);
   return true;
}

bool GUIManager::OnInternet (const CEGUI::EventArgs& e)
{
   return true;
}

bool GUIManager::OnExit (const CEGUI::EventArgs& e)
{
   sf::Event ev;
   ev.Type = sf::Event::Closed;
   return mEVH.HandleEvents( ev );
}


bool GUIManager::OnSelect (const CEGUI::EventArgs& e)
{
   // set FloorPlacement to Building
   // route mouse clicks that hit the main into the FloorPlacement manager.
   return mEVH.HandleEvents (HR_SelectBuildCursor);  // this only sets the strategy.
}

// move to tools

bool GUIManager::OnRemove (const CEGUI::EventArgs& e)
{

   // route mouse clicks that hit the main into the FloorPlacement manager.
   return mEVH.HandleEvents  (HR_PlaceStairs);  // this only sets the strategy.
}

bool GUIManager::OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
   // remember, this is just the GUI code, mouse downs for the Park are passed through to the 3D system
   //// SUPERULTRABUGGYFANTASTIC atm.
   //if (mPlacingRoom || mRoom) {
   //   std::cout << "This part should place the room!\n";
   //   mRoom->SetX(Scene.x);
   //   mRoom->SetY(1);
   //   mPark->GetPathway(1)->AddFloor(mRoom);
   //   //mPark.AddRoom(mRoom);
   //   mPlacingRoom = false;
   //   mRoom = NULL;
   //} else {
      return mpSystem->injectMouseButtonDown(CEMouseButton(Button));
   //}
}

bool
GUIManager::OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
   return mpSystem->injectMouseButtonUp(CEMouseButton(Button));
}

bool
GUIManager::OnKeyDown (sf::Key::Code Key)
{
   return mpSystem->injectKeyDown(CEKey(Key));
}

bool
GUIManager::OnKeyUp (sf::Key::Code Key)
{
   return mpSystem->injectKeyUp(CEKey(Key));
}

bool
GUIManager::OnMouseMove (Vector2i Scene, Vector2i Cam)
{
   return mpSystem->injectMousePosition(float(Cam.x), float(Cam.y));
}

bool
GUIManager::OnMouseWheel (int Delta)
{
   if (mpSystem->injectMouseWheelChange(float(Delta))) {
      std::cout << "GUIManager ate MouseWheel (OMNOMNOM now make me a sandwich)" << std::endl;
      return true;
   }
   else
      return false;
}

bool GUIManager::OnResize(Vector2i NewSize)
{
   // We need to manually resize the space the GUI is being drawn on so that things are not streched.
   // For some reason, this doesn't work.
   //mpRootWind->setSize(CEGUI::UVector2(CEGUI::UDim(0, NewSize.x*10), CEGUI::UDim(1, NewSize.y)));
   mpRenderer->setDisplaySize(CEGUI::Size((float)NewSize.x, (float)NewSize.y));
   //std::cout << "Set the size of the CEGUI window! (" << NewSize.x << ", " << NewSize.y << ")\n";
   return false;
}



/************************************************************************/
/*                              Private                                 */
/************************************************************************/

CEGUI::Key::Scan
GUIManager::CEKey (sf::Key::Code Code)
{
	if (mKeyMap.find(Code) == mKeyMap.end())
		return (CEGUI::Key::Scan)0;

	return mKeyMap[Code];
}

CEGUI::MouseButton
GUIManager::CEMouseButton (sf::Mouse::Button Button)
{
	if (mMouseButtonMap.find(Button) == mMouseButtonMap.end())
		return (CEGUI::MouseButton)0;

	return mMouseButtonMap[Button];
}

//Auto-generated (phew...), edited by hand
void
GUIManager::InitMaps()
{
	mKeyMap[sf::Key::Escape]          = CEGUI::Key::Escape       ;
	mKeyMap[sf::Key::Num1]            = CEGUI::Key::One          ;
	mKeyMap[sf::Key::Num2]            = CEGUI::Key::Two          ;
	mKeyMap[sf::Key::Num3]            = CEGUI::Key::Three        ;
	mKeyMap[sf::Key::Num4]            = CEGUI::Key::Four         ;
	mKeyMap[sf::Key::Num5]            = CEGUI::Key::Five         ;
	mKeyMap[sf::Key::Num6]            = CEGUI::Key::Six          ;
	mKeyMap[sf::Key::Num7]            = CEGUI::Key::Seven        ;
	mKeyMap[sf::Key::Num8]            = CEGUI::Key::Eight        ;
	mKeyMap[sf::Key::Num9]            = CEGUI::Key::Nine         ;
	mKeyMap[sf::Key::Num0]            = CEGUI::Key::Zero         ;
	mKeyMap[sf::Key::Dash]            = CEGUI::Key::Minus        ;
	mKeyMap[sf::Key::Equal]           = CEGUI::Key::Equals       ;
	mKeyMap[sf::Key::Back]            = CEGUI::Key::Backspace    ;
	mKeyMap[sf::Key::Tab]             = CEGUI::Key::Tab          ;
	mKeyMap[sf::Key::Q]               = CEGUI::Key::Q            ;
	mKeyMap[sf::Key::W]               = CEGUI::Key::W            ;
	mKeyMap[sf::Key::E]               = CEGUI::Key::E            ;
	mKeyMap[sf::Key::R]               = CEGUI::Key::R            ;
	mKeyMap[sf::Key::T]               = CEGUI::Key::T            ;
	mKeyMap[sf::Key::Y]               = CEGUI::Key::Y            ;
	mKeyMap[sf::Key::U]               = CEGUI::Key::U            ;
	mKeyMap[sf::Key::I]               = CEGUI::Key::I            ;
	mKeyMap[sf::Key::O]               = CEGUI::Key::O            ;
	mKeyMap[sf::Key::P]               = CEGUI::Key::P            ;
	mKeyMap[sf::Key::LBracket]        = CEGUI::Key::LeftBracket  ;
	mKeyMap[sf::Key::RBracket]        = CEGUI::Key::RightBracket ;
	mKeyMap[sf::Key::Return]          = CEGUI::Key::Return       ;
	mKeyMap[sf::Key::LControl]        = CEGUI::Key::LeftControl  ;
	mKeyMap[sf::Key::A]               = CEGUI::Key::A            ;
	mKeyMap[sf::Key::S]               = CEGUI::Key::S            ;
	mKeyMap[sf::Key::D]               = CEGUI::Key::D            ;
	mKeyMap[sf::Key::F]               = CEGUI::Key::F            ;
	mKeyMap[sf::Key::G]               = CEGUI::Key::G            ;
	mKeyMap[sf::Key::H]               = CEGUI::Key::H            ;
	mKeyMap[sf::Key::J]               = CEGUI::Key::J            ;
	mKeyMap[sf::Key::K]               = CEGUI::Key::K            ;
	mKeyMap[sf::Key::L]               = CEGUI::Key::L            ;
	mKeyMap[sf::Key::SemiColon]       = CEGUI::Key::Semicolon    ;
	mKeyMap[sf::Key::LShift]          = CEGUI::Key::LeftShift    ;
	mKeyMap[sf::Key::BackSlash]       = CEGUI::Key::Backslash    ;
	mKeyMap[sf::Key::Z]               = CEGUI::Key::Z            ;
	mKeyMap[sf::Key::X]               = CEGUI::Key::X            ;
	mKeyMap[sf::Key::C]               = CEGUI::Key::C            ;
	mKeyMap[sf::Key::V]               = CEGUI::Key::V            ;
	mKeyMap[sf::Key::B]               = CEGUI::Key::B            ;
	mKeyMap[sf::Key::N]               = CEGUI::Key::N            ;
	mKeyMap[sf::Key::M]               = CEGUI::Key::M            ;
	mKeyMap[sf::Key::Comma]           = CEGUI::Key::Comma        ;
	mKeyMap[sf::Key::Period]          = CEGUI::Key::Period       ;
	mKeyMap[sf::Key::Slash]           = CEGUI::Key::Slash        ;
	mKeyMap[sf::Key::RShift]          = CEGUI::Key::RightShift   ;
	mKeyMap[sf::Key::Multiply]        = CEGUI::Key::Multiply     ;
	mKeyMap[sf::Key::LAlt]            = CEGUI::Key::LeftAlt      ;
	mKeyMap[sf::Key::Space]           = CEGUI::Key::Space        ;
	mKeyMap[sf::Key::F1]              = CEGUI::Key::F1           ;
	mKeyMap[sf::Key::F2]              = CEGUI::Key::F2           ;
	mKeyMap[sf::Key::F3]              = CEGUI::Key::F3           ;
	mKeyMap[sf::Key::F4]              = CEGUI::Key::F4           ;
	mKeyMap[sf::Key::F5]              = CEGUI::Key::F5           ;
	mKeyMap[sf::Key::F6]              = CEGUI::Key::F6           ;
	mKeyMap[sf::Key::F7]              = CEGUI::Key::F7           ;
	mKeyMap[sf::Key::F8]              = CEGUI::Key::F8           ;
	mKeyMap[sf::Key::F9]              = CEGUI::Key::F9           ;
	mKeyMap[sf::Key::F10]             = CEGUI::Key::F10          ;
	mKeyMap[sf::Key::Numpad7]         = CEGUI::Key::Numpad7      ;
	mKeyMap[sf::Key::Numpad8]         = CEGUI::Key::Numpad8      ;
	mKeyMap[sf::Key::Numpad9]         = CEGUI::Key::Numpad9      ;
	mKeyMap[sf::Key::Subtract]        = CEGUI::Key::Subtract     ;
	mKeyMap[sf::Key::Numpad4]         = CEGUI::Key::Numpad4      ;
	mKeyMap[sf::Key::Numpad5]         = CEGUI::Key::Numpad5      ;
	mKeyMap[sf::Key::Numpad6]         = CEGUI::Key::Numpad6      ;
	mKeyMap[sf::Key::Add]             = CEGUI::Key::Add          ;
	mKeyMap[sf::Key::Numpad1]         = CEGUI::Key::Numpad1      ;
	mKeyMap[sf::Key::Numpad2]         = CEGUI::Key::Numpad2      ;
	mKeyMap[sf::Key::Numpad3]         = CEGUI::Key::Numpad3      ;
	mKeyMap[sf::Key::Numpad0]         = CEGUI::Key::Numpad0      ;
	mKeyMap[sf::Key::F11]             = CEGUI::Key::F11          ;
	mKeyMap[sf::Key::F12]             = CEGUI::Key::F12          ;
	mKeyMap[sf::Key::F13]             = CEGUI::Key::F13          ;
	mKeyMap[sf::Key::F14]             = CEGUI::Key::F14          ;
	mKeyMap[sf::Key::F15]             = CEGUI::Key::F15          ;
	mKeyMap[sf::Key::RControl]        = CEGUI::Key::RightControl ;
	mKeyMap[sf::Key::Divide]          = CEGUI::Key::Divide       ;
	mKeyMap[sf::Key::RAlt]            = CEGUI::Key::RightAlt     ;
	mKeyMap[sf::Key::Pause]           = CEGUI::Key::Pause        ;
	mKeyMap[sf::Key::Home]            = CEGUI::Key::Home         ;
	mKeyMap[sf::Key::Up]              = CEGUI::Key::ArrowUp      ;
	mKeyMap[sf::Key::PageUp]          = CEGUI::Key::PageUp       ;
	mKeyMap[sf::Key::Left]            = CEGUI::Key::ArrowLeft    ;
	mKeyMap[sf::Key::Right]           = CEGUI::Key::ArrowRight   ;
	mKeyMap[sf::Key::End]             = CEGUI::Key::End          ;
	mKeyMap[sf::Key::Down]            = CEGUI::Key::ArrowDown    ;
	mKeyMap[sf::Key::PageDown]        = CEGUI::Key::PageDown     ;
	mKeyMap[sf::Key::Insert]          = CEGUI::Key::Insert       ;
	mKeyMap[sf::Key::Delete]          = CEGUI::Key::Delete       ;

	mMouseButtonMap[sf::Mouse::Left]		= CEGUI::LeftButton;
	mMouseButtonMap[sf::Mouse::Middle]		= CEGUI::MiddleButton;
	mMouseButtonMap[sf::Mouse::Right]		= CEGUI::RightButton;
	mMouseButtonMap[sf::Mouse::XButton1]	= CEGUI::X1Button;
	mMouseButtonMap[sf::Mouse::XButton2]	= CEGUI::X2Button;
}
