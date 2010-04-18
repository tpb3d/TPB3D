/*This file is part of Theme Park Builder 3D The Game.
*
*Theme Park Builder 3D The Game is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.

*Theme Park Builder 3D The Game is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../Resources.h"

#include <cstring>
#include <iostream>
#include <string>

//#include "GLee/GLee.h"	//GL header file, including extensions
#include "Matrix16.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Physics/MotionPhysics.h"
#include "../Scene/Scene.h"
#include "../AI/PeepAgent.h"
#include "../AI/PeepAgent.h"
//#include "../Window/ToolBar.h"

#include "Image.h"
#include "Animation.h"
#include "ModelObject.h"   // 3d abstract
#include "ViewObject.h"    // 2d abstract

#include "Camera.h"

float gLightPosition[] = { 0, 500.0f, 50, 0.0f };
float gSpotPosition[] = { -95.0f, 295.0f, -120.0f, 1.0f };
float LightDirection[]= {  0.05f, -1.0f, 0.01f };
float SpotDirection[]= {  0.35f, -0.75f, 0.0f };
const GLfloat LightOff[]=	{ 0.0f, 0.0f, 0.0f, 1.0f }; // just a little
const GLfloat SpotCutoff =	75.0f;
const GLfloat SpecRef[]= {  0.45f, 0.55f, 0.75f, 1.0f };

#define FIELD_OF_VIEW 45.0f  // this controls how long the focal view of the camera is in OpenGL
Camera * Camera::mpInstance = NULL;

Camera::Camera ()
:  Body (960, 720)
{
   sf::WindowSettings Settings;
   Settings.DepthBits         = 24; // Request a 24 bits depth buffer
   Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
   Settings.AntialiasingLevel = 2;  // Request 2 Pathways of antialiasing
   mpWindow = new sf::RenderWindow ();
   mpWindow->Create (sf::VideoMode ((unsigned int)mWidth.x, (unsigned int)mHeight.y, 32), "Theme Park Builder 3D The Game (version " HR_VERSION ")", sf::Style::Close|sf::Style::Resize, Settings);
   //mpWindow->SetPosition( 0, 100);
   mZoomFactor = -100; // back away 100 feet
   mAspect = (float)(mWidth.x / mHeight.y);
   mCam.x = mWidth.x;
   mCam.y = mHeight.y;
   mIgnoreCamera = false;
   mpInput = &(mpWindow->GetInput ());
   mPosition.x = 0.0;
   mPosition.y = 0.0;
   mPosition.z = 0.0;
   mpWindow->ShowMouseCursor (false);

   mTarget.x = 35.0;
   mTarget.y = 90.0;
   mTarget.z = 0.0;

   mMousePos.x = 0;
   mMousePos.y = 0;

   memset(keylist, 0, 256);
   memset(btnlist, 0, 4);
}

const sf::Input * Camera::GetInput ()
{
   return mpInput;
}

Vector2i Camera::GetMouse ()
{
   Vector2f ms2( mPosition.x, mPosition.y );
   return ms2 + GetLocalMouse();
}

Vector2i Camera::GetLocalMouse()
{
   return Vector2i (mpInput->GetMouseX (), mpInput->GetMouseY ());
}


void Camera::SetMaxFramerate (int rate)
{
   mpWindow->SetFramerateLimit (rate);
}

void Camera::SetSceneSize (Vector2f Size)
{
   glClearDepth(1.0f);
   mScene.x = Size.x;
   mScene.y = Size.y;
}

Camera* Camera::GetInstance()
{
   if (mpInstance == NULL)
   {
      mpInstance = new Camera ();
   }
   return mpInstance;
}

// modes functions
void Camera::Clear ()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
}

void Camera::SetActive()
{
   //	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear Screen And Depth Buffer
   glViewport(0, 0, (GLsizei)mCam.x, (GLsizei)mCam.y);//this->ms.x, ms.y); these were negative need to fixe this so the
   glMatrixMode(GL_MODELVIEW);

   // This is probably the wrong place for these

   // Move camera forward
   if (keylist[sf::Key::W])
   {
      if(mZoomFactor < -5)
      {
         Move(0.0f, 0.0f, -0.01f * mZoomFactor);
      }
      else
      {
         Move(0.0f, 0.0f, 0.5f);
      }
   }

   // Move camera backward
   if (keylist[sf::Key::S])
   {
      if(mZoomFactor < -5)
      {
         Move(0.0f, 0.0f, 0.01f * mZoomFactor);
      }
      else
      {
         Move(0.0f, 0.0f, -0.5f);
      }
   }

   // Move camera left
   if (keylist[sf::Key::A])
   {
      if(mZoomFactor < -5)
      {
         Move (-0.01f * mZoomFactor, 0.0f, 0.0f);
      }
      else
      {
         Move (0.5f, 0.0f, 0.0f);
      }
   }

   // Move camera right
   if (keylist[sf::Key::D])
   {
      if(mZoomFactor < -5)
      {
         Move (0.01f * mZoomFactor, 0.0f, 0.0f);
      }
      else
      {
         Move (-0.5f, 0.0f, 0.0f);
      }
   }

   // Change camera attitude
   if (keylist[sf::Key::Q])
   {
      mTarget.x += 1.0f;
   }
   if (keylist[sf::Key::E])
   {
      mTarget.x -= 1.0f;
   }

   // Change camera angle
   if (keylist[sf::Key::R])
   {
      mTarget.y += 2.0;
   }
   if (keylist[sf::Key::T])
   {
      mTarget.y -= 2.0;
   }

   // Rotate camera xy, with middle mouse button.
   if(btnlist[sf::Mouse::Middle])
   {
      Vector2i mv2i;
      mv2i.x = (GetLocalMouse().x) - (int)(mCam.x / 2);
      mv2i.y = (GetLocalMouse().y) - (int)(mCam.y / 2);

      mTarget.x += float(mv2i.y - mMousePos.y) / 4;
      mTarget.y += float(mv2i.x - mMousePos.x) / 4;
      mMousePos.x = mv2i.x;
      mMousePos.y = mv2i.y;
   } else {
      Vector2i mv2i;
      mv2i.x = (GetLocalMouse().x) - (int)(mCam.x / 2);
      mv2i.y = (GetLocalMouse().y) - (int)(mCam.y / 2);
      mMousePos.x = mv2i.x;
      mMousePos.y = mv2i.y;
   }

   // Set camera
   glTranslatef(0.0f, 0.0f, mZoomFactor); // Camera center, point of rotation
   glRotatef (mTarget.x, 1.0f, 0.0f, 0.0f);
   glRotatef (mTarget.y, 0.0f, 1.0f, 0.0f);
   glRotatef (mTarget.z, 0.0f, 0.0f, 1.0f);

   glTranslatef(mPosition.x, mPosition.y, mPosition.z); // Translate camera


   //   mpWindow->SetActive (true);
   glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);	// mLightPosition// Position The Light
   glLightfv(GL_LIGHT1, GL_POSITION, gSpotPosition);	// Position The Light
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotDirection);	// Position The Light
   glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, SpotCutoff);	// Limit The Light
   glMaterialfv(GL_FRONT, GL_EMISSION, LightOff );
}

void Camera::Display ()
{
   mpWindow->Display ();
}

void Camera::Center (int x, int y)
{
   mPosition.x = -0; //x - (mViewRect.Left / 2);
   mPosition.y = -0; //y - (mViewRect.Top / 2);
   mPosition.z = 20; //y - (mViewRect.Top / 2);
}

bool Camera::OnResize (Vector2i vi)
{
   glViewport(0, 0, vi.x, vi.y);
   mCam = vi;
   mAspect = (float)(vi.x) / vi.y;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective (FIELD_OF_VIEW, mAspect ,0.5f,1000.0f);		// Calculate The Aspect Ratio Of The Window
   return true;
}

void Camera::InitGL()
{
   glShadeModel(GL_SMOOTH);												// Enable Smooth Shading
   glClearDepth(1.0f);														// Depth Buffer Setup
   glClearColor(0.f, 0.f, 0.f, 0.f);

   // Enable Z-buffer read and write
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
   glDepthFunc(GL_LEQUAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);						// Really Nice Perspective Calculations

   // Setup a perspective projection
   mAspect = (float)(mCam.x) / mCam.y;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective (FIELD_OF_VIEW, mAspect, 0.5f, 1000.f);
   glEnable (GL_TEXTURE_2D);
   InitLighting();

   const GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };	// Storage For Three Types Of Fog
   const GLuint fogfilter= 1;					// Which Fog To Use
   const GLfloat fogColor[4]= {0.25f, 0.3f, 0.35f, 0.5f};		// Fog Color


   glFogi(GL_FOG_MODE, fogMode[fogfilter]);		// Fog Mode
   glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
   glFogf(GL_FOG_DENSITY, 0.005f);				// How Dense Will The Fog Be
   glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
   glFogf(GL_FOG_START, 100.0f);				// Fog Start Depth
   glFogf(GL_FOG_END, 101.0f);				// Fog End Depth

   //Use the color as the ambient and diffuse material
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
}

void Camera::InitLighting()
{
   const GLfloat LightBlazing[]=	{ 1.0, 1.0, 1.0, 1.0 };
   //const GLfloat LightSpecular[]= { 0.25f, 0.35f, 0.3f, 0.5f };
   //const GLfloat LightAmbient[]=	{ 0.45f, 0.40f, 0.35f, 1.0f }; // day glow
   //const GLfloat LightDiffuse[]=	{ 0.38f, 0.37f, 0.38f, 0.45f };

   //const GLfloat SpotSpecular[] = { 0.55f, 0.47f, 0.17f, 0.75f };
   //const GLfloat SpotAmbient[]=	 { 0.47f, 0.68f, 0.48f, 0.85f }; // bright ng vapor street light
   //const GLfloat SpotDiffuse[]=	 { 0.47f, 0.46f, 0.49f, 0.65f };
   const GLfloat LightSpecular[]= { 0.25f, 0.35f, 0.3f, 0.5f };
   const GLfloat LightAmbient[]=	{ 0.15f, 0.10f, 0.05f, 0.5f }; // day glow
   const GLfloat LightDiffuse[]=	{ 0.08f, 0.07f, 0.08f, 0.45f };

   const GLfloat SpotSpecular[] = { 0.25f, 0.17f, 0.17f, 0.5f };
   const GLfloat SpotAmbient[]=	 { 0.17f, 0.18f, 0.18f, 0.5f }; // bright ng vapor street light
   const GLfloat SpotDiffuse[]=	 { 0.17f, 0.16f, 0.19f, 0.5f };

   //GLfloat SpotOn[]={ 0.0f, -20.0f, -20.0f, -40.0 };
   const GLfloat UplightDirection[]={ 0.0f, 1.0f, 0.0f };
   const GLfloat LightLow[]=	{ 0.25f, 0.25f, 0.25f, 0.25f }; // just a little
   const GLfloat specular [] = { 1.0f, 1.0f, 1.0f, 0.8f };
   const GLfloat shininess = 0.85f;

   //mLightBrightness = 0.25f;
   //mAmbiantBrightness = 0.75f;
   //mSpotBrightness = 0.5f;
   //mSpotPosition[0] = 5.0f;
   //mSpotPosition[1] = 35.0f;
   //mSpotPosition[2] = -20.0f;
   //mSpotPosition[3] = 1.0f;

   //LightPosition[0] = 0.0f;
   //LightPosition[1] = 30.0f;
   //LightPosition[2] = 0.0f;
   //LightPosition[3] = 1.0f;
   glEnable(GL_DEPTH_TEST);					// Enables Depth Testing
   //   glFrontFace( GL_CCW );
   //	glEnable(GL_CULL_FACE);
   glDepthFunc(GL_LEQUAL);						// The Type Of Depth Testing To Do
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);						// Really Nice Perspective Calculations
   glShadeModel (GL_SMOOTH);					// Select Smooth Shading


   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glLightfv(GL_LIGHT0, GL_AMBIENT,  LightAmbient);		// Setup The Ambient Light
   glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);	// mLightPosition// Position The Light
   glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);		// Setup The Specular Light
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightDiffuse);		// Setup The Diffuse Light
   glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION,  0.025f);		// Setup The Strength of Light
   glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);

   glEnable(GL_LIGHT1);
   glLightfv(GL_LIGHT1, GL_AMBIENT,  SpotAmbient);		// Setup The Ambient Light
   glLightfv(GL_LIGHT1, GL_SPECULAR, SpotSpecular);		// Setup The Specular Light
   glLightfv(GL_LIGHT1, GL_DIFFUSE,  SpotDiffuse);		// Setup The Diffuse Light
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotDirection); // Facing, down?
   glLightf( GL_LIGHT1, GL_SPOT_EXPONENT, 15.0f ); // ?
   glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);		// Setup The Strength of Light
   glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0025f);		// Setup The Strength of Light
   glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);		// Setup The Strength of Light

   glLightfv(GL_LIGHT1, GL_POSITION, gSpotPosition);	// Position The Light


   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void Camera::DrawModel (Scene* pModel)   // 3d interface objects
{
   //glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
   //glLoadIdentity();									// Reset The Projection Matrix
   glMatrixMode(GL_MODELVIEW);
   glEnable (GL_LIGHTING);
   glPushMatrix();
   {                       // brackets just keep the code in push and pop uniform
      glEnable (GL_TEXTURE_2D);
      glColor4ub (255,255,255,255);
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
      glEnable(GL_BLEND);
      pModel->Draw();
      glDisable(GL_BLEND);
   }
   glPopMatrix();
   glDisable (GL_LIGHTING);
   glMatrixMode(GL_MODELVIEW);						// Select The Projection Matrix
}

void Camera::DrawInterface(Interface* pI)   // 2d interface objects
{
   glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
   glPushMatrix();										// Store The Projection Matrix
   {
      glLoadIdentity();									// Reset The Projection Matrix
      glOrtho( 0, mWidth.x, 0, mHeight.y, -1, 1);	   // Set Up An Ortho Screen zero is at the bottom
      glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
      glPushMatrix();										// Store The Modelview Matrix
      {
         glLoadIdentity();									// Reset The Modelview Matrix
         glEnable (GL_TEXTURE_2D);
         glColor4ub (255,255,255,255);
         glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
         glEnable(GL_BLEND);
         pI->Draw();
         glDisable(GL_BLEND);
      }
      glMatrixMode(GL_MODELVIEW);						// Select The Projection Matrix
      glPopMatrix();										// Restore The Old Projection Matrix
   }
   glMatrixMode(GL_PROJECTION );							// Select The Modelview Matrix
   glPopMatrix();										// Restore The Old Projection Matrix
   glMatrixMode(GL_MODELVIEW);						// Select The Projection Matrix
   glEnable (GL_TEXTURE_2D);
   glColor4ub (255,255,255,255);
}

#define BUFFER_LENGTH 64   // max click hits we expect but we might get 2
int  Camera::TranslateX (Scene* pModel, Vector2f mouse)
{
   return (int)(mouse.x * mAspect / 9)-34; // still has an error
}


int Camera::DrawSelectionTarget (Scene* pModel, Vector2f mouse, int Pathway)
{
   int iResult = 0;

   glPushAttrib(GL_ALL_ATTRIB_BITS);

   glDisable (GL_LIGHTING);
   // Space for selection buffer
   GLuint selectBuff[BUFFER_LENGTH];

   // Hit counter and viewport storeage
   GLint hits, viewport[4];

   // Setup selection buffer
   glSelectBuffer(BUFFER_LENGTH, selectBuff);

   // Get the viewport
   glGetIntegerv(GL_VIEWPORT, viewport);

   // Switch to projection and save the matrix
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();

   // Change render mode
   glRenderMode(GL_SELECT);

   // Establish new clipping volume to be unit cube around
   // mouse cursor point (xPos, yPos) and extending two pixels
   // in the vertical and horzontal direction
   glLoadIdentity();
   glInitNames();
   glPushName(0);

   gluPickMatrix(mouse.x, viewport[3]-mouse.y, 2, 2, viewport); // mouse y is inverted

   // Apply perspective matrix
   gluPerspective (FIELD_OF_VIEW, mAspect, 0.5f, 1000.f);		// Calculate The Aspect Ratio Of The Window
   glTranslatef (GetPositionX(), GetPositionY(), mZoomFactor);

   // Draw the scene
   pModel->DrawSelectionTarget (Pathway); // is Pathway is not Zero then we run a render check on that Pathway else we do the whole Park

   // Collect the hits
   hits = glRenderMode(GL_RENDER);

   // Restore the projection matrix
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();

   // Go back to modelview for normal rendering
   glMatrixMode(GL_MODELVIEW);

   // If a single hit occured, display the info.
   GLuint nHit = 0;
   if(hits == 1)
   {
      //      MakeSelection(selectBuff[3]);
      if(nHit != selectBuff[3])
      {
         iResult = selectBuff[3]; // ok what did we hit
      }
   }
   glPopAttrib();
   return iResult; // the object id
}

Vector3f Camera::GetOGLPos (Vector2f winVec) // NeHe Productions at GameDev
{
   // this little magic function takes the mouse position in view coordinates and transforms it through
   // the same GL Matrix as the scene. This is then adjusted for the building positon.
   GLint viewport[4];
   GLdouble modelview[16];
   GLdouble projection[16];

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();

   glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
   glGetDoublev( GL_PROJECTION_MATRIX, projection );
   glGetIntegerv( GL_VIEWPORT, viewport );


   GLfloat winX = winVec.x;
   GLfloat winY = winVec.y;//(float)viewport[3] - winVec.y;
   GLfloat winZ[16];
   memset (winZ, 0, sizeof(winZ));
   glReadPixels ((int)winX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, winZ );

   GLdouble posX = 0;
   GLdouble posY = 0;
   GLdouble posZ = 0;
   gluUnProject( winX, winY, winZ[0], modelview, projection, viewport, &posX, &posY, &posZ);

   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();


   return Vector3f((float)posX-GetPositionX(), (float)posY+GetPositionY(), (float)posZ); // +GetPositionX());
}

bool
Camera::GetEvent (sf::Event & event)
{
   return mpWindow->GetEvent (event);
}


Vector3f Camera::GetOGLPos2(float zFar, float zNear, Vector3f v)
{
   //float z = t;
   float a = zFar / ( zFar - zNear );
   float b = zFar * zNear / ( zNear - zFar );
   float z_buffer_value = ( a + b / v.z );

   GLint viewport[4];
   GLdouble modelview[16];
   GLdouble projection[16];
   GLfloat winX, winY, winZ;
   GLdouble posX, posY, posZ;


   glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
   glGetDoublev( GL_PROJECTION_MATRIX, projection );
   glGetIntegerv( GL_VIEWPORT, viewport );

   winX = (float)v.x;
   winY = (float)viewport[3] - (float)v.y;
   glReadPixels( (int)v.x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

   gluUnProject( winX, winY, z_buffer_value, modelview, projection, viewport, &posX, &posY, &posZ);

   return Vector3f ((float)posX, (float)posY, (float)posZ);
}

void Camera::Move(float x, float y, float z)
{
   const double RAD = 57.29577851; // Radians, I don't know if this is already declared somewhere?
   double lx = 0;
   double lz = 0;

    // Move along camera angle on the X axis
   if(x < 0)
   {
      lz = +sin( -(mTarget.y / RAD) );
      lx = -cos( -(mTarget.y / RAD) );

      mPosition.x += (float)(1.0* lx * -x);
      mPosition.z += (float)(1.0* lz * -x);
   }

   if(x > 0)
   {
      lz = +sin( -(mTarget.y / RAD) );
      lx = -cos( -(mTarget.y / RAD) );

      mPosition.x -= (float)(1.0 * lx * x);
      mPosition.z -= (float)(1.0 * lz * x);
   }

   // Move along camera angle on the Z axis
   if(z < 0)
   {
      lx = +sin( -(mTarget.y / RAD) );
      lz = -cos( -(mTarget.y / RAD));

      mPosition.x -= (float)(1.0 * lx * -z);
      mPosition.z += (float)(1.0 * lz * -z);
   }

   if(z > 0)
   {
      lx = +sin( -(mTarget.y / RAD) );
      lz = -cos( -(mTarget.y / RAD) );

      mPosition.x += (float)(1.0 * lx * z);
      mPosition.z -= (float)(1.0 * lz * z);
   }
}

bool Camera::OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
   btnlist[Button] = false;
   return false;
}

bool Camera::OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
   btnlist[Button] = true;
   return false;
}

bool Camera::OnKeyUp (sf::Key::Code Key)
{
   keylist[Key] = false;
   return true;
}

bool Camera::OnKeyDown (sf::Key::Code Key)
{
   keylist[Key] = true;
   return true;
}

bool Camera::OnMouseWheel (int Delta)
{
   if (Delta > 0)
   {
      Zoom (5);

      // Zoom in to the mouse pointer. The code doens't work perfactly, but it's pretty close.
      Vector2i mv2i; // Mouse Vector 2i
      mv2i.x = (GetLocalMouse().x) - (int)(mCam.x / 2);
      mv2i.y = (GetLocalMouse().y) - (int)(mCam.y / 2);

      // Figure out how much OGL space is between one mouse unit
      glLoadIdentity(); // Reset OGL matrix, keeps rotation and translation from affecting this
      Vector3f vf1 = GetOGLPos2(1000.0, 0.5, Vector3f( 1, 1, mZoomFactor) );
      Vector3f vf2 = GetOGLPos2(1000.0, 0.5, Vector3f( 2, 2, mZoomFactor) );

      float x = -fabs(vf1.x-vf2.x);
      float y = -fabs(vf1.y-vf2.y);

      // I don't know why I have to divide these by such a random value.
      Move( -(mv2i.x*x) / (mZoomFactor / 6), 0, 0);
      Move(0, 0, -(mv2i.y*y) / (mZoomFactor / 8) );

   }
   else
   {
      Zoom(-5.0f);
   }
   // zoom height and tilt
   //float ang = mZoomFactor/ 600*90;
   //float x = (float)(cos(0.01745329 * (180.0 + ang)));
   //float y = (float)(sin(0.01745329 * (180.0 - ang)) * 200);
   //mPosition.y = y-8;
   //mTarget.x = -ang;

   return true;
}

void Camera::Zoom(float Factor)
{
   //Rectf ZoomedRect;
   // Calcuate the center
   if(( Factor < 0 && mZoomFactor > -600 )||( Factor > 0 && mZoomFactor < 0 ))
   {
      mZoomFactor += Factor;
   }
   //std::cout << "ZF=" << mZoomFactor << "\n";
}
