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



GVersion version = GVersion(0);
float COMMIT_TIME_INTERVAL = 1.0;
float g_time = 0.0;			// in seconds
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
	g_Camera.PositionCamera(0, 1.5f, 6,   0, 1.5f, 0,   0, 1, 0);
	loadgalaxytextures();
	
}

void initVersions() {
	// Testing data
		XMLParser xmlParser = XMLParser();
	for (int i=78;i<81;i++) {
		xmlParser.parse(i,version);
		_RPT1( 0, "initVersions : %i\n", i);
	}
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
	

	int pIndex = 0;
	foreach(package,(version.childPackages),vector<GPackage>) {
		glPushMatrix();
		drawPackage(*package,pIndex);
		glPopMatrix();
		pIndex++;
	}
	

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
