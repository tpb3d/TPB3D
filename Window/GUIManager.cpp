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
#include <iostream>
#include <string>
#include "../Utility/GameException.h"

#include "../Hub/Event.h"
#include "GUIManager.h"

GUIManager::GUIManager(EventHandler& revh, Interface& rInterface)
:  mEVH (revh)
,  mInterface (rInterface)
{
}

GUIManager::~GUIManager()
{
}

bool GUIManager::OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
   return false;
}

bool
GUIManager::OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
   return false;
}

bool
GUIManager::OnKeyDown (sf::Key::Code Key)
{
   return false;
}

bool
GUIManager::OnKeyUp (sf::Key::Code Key)
{
   return false;
}

bool
GUIManager::OnMouseMove (Vector2i Scene, Vector2i Cam)
{
   return false;
}

bool
GUIManager::OnMouseWheel (int Delta)
{
   return false;
}

bool GUIManager::OnResize(Vector2i NewSize)
{
   return false;
}

