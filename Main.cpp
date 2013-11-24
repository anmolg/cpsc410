// This is a compiler directive that includes libraries (For Visual Studio)
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "main.h"										// This includes our header file
#include "Camera.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* g_time */
CCamera g_Camera;										// This is our global camera object

bool  g_bFullScreen = true;								// Set full screen as default
HWND  g_hWnd;											// This is the handle for the window
RECT  g_rRect;											// This holds the window dimensions
HDC   g_hDC;											// General HDC - (handle to device context)
HGLRC g_hRC;											// General OpenGL_DC - Our Rendering Context for OpenGL
HINSTANCE g_hInstance;									// This holds the global hInstance for UnregisterClass() in DeInit()

GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
//Add positioned light
GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
GLfloat lightPos0[] = {0.0f, 15.0f, 0.0f, 1.0f}; //Positioned at (4, 0, 8)
GLfloat lightPos1[] = {0.0f, 45.0f, 0.0f, 1.0f}; //Positioned at (4, 0, 8)
GLfloat lightPos2[] = {0.0f, -15.0f, 0.0f, 1.0f}; //Positioned at (4, 0, 8)
GLfloat lightPos3[] = {0.0f, -45.0f, 0.0f, 1.0f}; //Positioned at (4, 0, 8)

GVersion version = GVersion(0);
float COMMIT_TIME_INTERVAL = 4.0;

float commitNumber;

///////////////////////////////// INIT GAME WINDOW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function initializes the game window.
/////
///////////////////////////////// INIT GAME WINDOW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void Init(HWND hWnd)
{
	g_hWnd = hWnd;										// Assign the window handle to a global window handle
	GetClientRect(g_hWnd, &g_rRect);					// Assign the windows rectangle to a global RECT
	InitializeOpenGL(g_rRect.right, g_rRect.bottom);	// Init OpenGL with the global rect
	initVersions();
	// Init our camera position
	srand (time(NULL));
	// Position        View		   Up Vector
	g_Camera.PositionCamera(0, -10.0f, 50,   0, -10.0f, 0,   0, 1, 0);
	loadgalaxytextures();

}

float g_time = 0.0;			// initial time , in seconds
void initVersions() {
	// Testing data
	XMLParser xmlParser = XMLParser();
	for (int i=1;i<15;i++) {
		xmlParser.parse(i,version);
		_RPT1( 0, "initVersions : %i\n", i);
	}
	GitlogParser glParser = GitlogParser();
	glParser.glparse(version);
}

/////////////////////////////// ANIMATE NEXT FRAME \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function clamps a specified frame rate for consistency
/////
/////////////////////////////// ANIMATE NEXT FRAME \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool AnimateNextFrame(int desiredFrameRate)
{
	static float lastTime = GetTickCount() * 0.001f;
	static float elapsedTime = 0.0f;

	float currentTime = GetTickCount() * 0.001f; // Get the g_time (milliseconds = seconds * .001)
	float deltaTime = currentTime - lastTime; // Get the slice of g_time
	float desiredFPS = 1.0f / desiredFrameRate; // Store 1 / desiredFrameRate

	elapsedTime += deltaTime; // Add to the elapsed g_time
	lastTime = currentTime; // Update lastTime

	// Check if the g_time since we last checked is greater than our desiredFPS
	if( elapsedTime > desiredFPS )
	{
		elapsedTime -= desiredFPS; // Adjust our elapsed g_time

		// Return true, to animate the next frame of animation
		return true;
	}

	// We don't animate right now.
	return false;
}


///////////////////////////////// MAIN LOOP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function handles the main loop
/////
///////////////////////////////// MAIN LOOP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

WPARAM MainLoop()
{
	MSG msg;
	while(1)											// Do our infinite loop
	{													// Check if there was a message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{ 
			if(msg.message == WM_QUIT)					// If the message wasn't to quit
				break;
			TranslateMessage(&msg);						// Find out what the message does
			DispatchMessage(&msg);						// Execute the message
		}
		else											// if there wasn't a message
		{ 		
			if(AnimateNextFrame(60))					// Make sure we only animate 60 FPS
			{
				g_time += (float)1/60.0;
				commitNumber = g_time/COMMIT_TIME_INTERVAL;
				g_Camera.Update();							// Update the camera information

				RenderScene();								// Render the scene every frame


			}
			else
			{
				Sleep(1);								// Let other processes work
			}
		} 
	}

	DeInit();											// Clean up and free all allocated memory

	return(msg.wParam);									// Return from the program
}



void RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The matrix
	g_Camera.Look();

	// Lighting effects
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_COLOR);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT4, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT5, GL_POSITION, lightPos3);


	int pIndex = 0;
	foreach(package,(version.childPackages),vector<GPackage>) {
		glPushMatrix();
		drawPackage(*package,pIndex);
		glPopMatrix();
		pIndex++;
	}

	glColor3f(1,1,1);

	glDisable(GL_LIGHTING);
	drawhud(version, min((int)commitNumber,version.authors.size()));

	// CreateSkyBox(0, 0, 0, 300, 150, 300);
	// Swap the backbuffers to the foreground
	SwapBuffers(g_hDC);									
}

///////////////////////////////// WIN PROC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function handles the window messages.
/////
///////////////////////////////// WIN PROC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

LRESULT CALLBACK WinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG    lRet = 0; 

	switch (uMsg)
	{ 
	case WM_SIZE:										// If the window is resized
		if(!g_bFullScreen)								// Do this only if we are in window mode
		{
			SizeOpenGLScreen(LOWORD(lParam),HIWORD(lParam));// LoWord=Width, HiWord=Height
			GetClientRect(hWnd, &g_rRect);					// Get the window rectangle
		}
		break; 

	case WM_KEYDOWN:

		switch(wParam) {								// Check if we hit a key
		case VK_ESCAPE:								// If we hit the escape key
			PostQuitMessage(0);						// Send a QUIT message to the window
			break;
		}
		break;

	case WM_CLOSE:										// If the window is being closes
		PostQuitMessage(0);								// Send a QUIT Message to the window
		break; 

	default:											// Return by default
		lRet = DefWindowProc (hWnd, uMsg, wParam, lParam); 
		break; 
	} 

	return lRet;										// Return by default
}
