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

GVersion version = GVersion(1);
float commitTimeInterval = 3.0;
float g_time = 0.0;
float commitNumber;

#define STAR_RADIUS 2
#define PLANET_RADIUS 1
#define PLANET_DISTANCE 5
#define MOON_RADIUS 0.5
#define MOON_DISTANCE 1
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
}

void initVersions() {
	// Testing data
	GMethod method1 = GMethod();
	method1.creationTime = 1; method1.methodName = "method1";

	GMethod method2 = GMethod();
	method2.creationTime = 2; method2.methodName = "method2";

	GClass class1 = GClass();
	class1.creationTime=1; class1.className = "class1";
	class1.author_a = 3; class1.author_j = 1; class1.author_s = 2;
	class1.childMethods.push_back(method1);
	class1.childMethods.push_back(method2); 

	GPackage package1 = GPackage(1,"package1");
	package1.childClasses.push_back(class1);

	GClass class2 = GClass(); class2.creationTime=2; class2.className="class2";
	class2.author_a = 2; class2.author_j = 5; class2.author_s = 3;
	package1.childClasses.push_back(class2);

	version.childPackages.push_back(package1);
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
				commitNumber = g_time/commitTimeInterval;
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

void drawSphere(float sphereRadius, float orbitRadius, float orbitSpeed)
{
	GLUquadricObj *pObj = gluNewQuadric();									// Push on a new matrix scope
	glRotatef(orbitSpeed*g_time*60,0,1,0);	
	glTranslatef(orbitRadius,0,0);
	glPushMatrix();
	glRotatef(60*g_time, 0, 1.0, 0);			// Rotate the sphere around itself to produce the spin
	gluSphere(pObj, sphereRadius, 8, 8);					// Draw the sphere with a radius of 0.1 (smallest planet)
	glPopMatrix();
}

void drawMethod(GMethod gm, int index) {
	// checking whether the moon should be displayed
	// displays when creationTime <= commitNumber < endTime
	if ((commitNumber < gm.creationTime) && (commitNumber >= gm.endTime)) return;
	glColor3f(1,1,1);
	//int randomAngle = rand()%360; // THIS DID NOT WORK BECUZ IT GENERATES RANDOM STUFF EVERY TIME
	//float randomX = rand()%100 / 100.0;
	//float randomZ = rand()%100/100.0;
	glRotatef(index*60,1,0,0); // arbitrary angles of rotation.
	drawSphere(MOON_RADIUS,index*MOON_DISTANCE,3); // Last parameter just for testing
	glColor3f(1,0,0);
}

void drawClass(GClass gc,int index) {
	if (commitNumber<gc.creationTime) return;
	int a = gc.author_a; int j = gc.author_j; int s = gc.author_s;
	float total = a+j+s;
	glColor3f(a/total,j/total,s/total);
	drawSphere(PLANET_RADIUS,index*PLANET_DISTANCE,1+index); // Last parameter is just for testing
	int i= 1;
	foreach(gmethod,gc.childMethods,vector<GMethod>) {
		glPushMatrix();
		drawMethod(*gmethod,i);
		glPopMatrix();
		i++;
	}
}

void drawPackage(GPackage gp) {
	if(commitNumber < gp.creationTime) return;
	drawSphere(STAR_RADIUS,0,0);
	int index = 1;
	foreach(gclass,gp.childClasses,vector<GClass>) {
		glPushMatrix();
		drawClass(*gclass,index);
		glPopMatrix();
		index++;
	}

}

void RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The matrix
	g_Camera.Look();
	glColor3f(1,0,0);

	foreach(package,(version.childPackages),vector<GPackage>) {
		drawPackage(*package);
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
