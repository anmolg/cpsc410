#include "hud.h"
#include "Model.h"
#define EDGE_WIDTH 50

UINT hudtexture[6];

bool ishudtextureloaded=false;

float hpBarLength=SCREEN_WIDTH*34.4/100;
float hpBarLeft=SCREEN_WIDTH*5/100-SCREEN_HEIGHT*3.1/100;

float expBarLength=SCREEN_WIDTH*31.5/100;
float expBarLeft=SCREEN_WIDTH*5.60/100-SCREEN_HEIGHT*3.1/100;

float button_h=SCREEN_HEIGHT*0.08;
float button_w=SCREEN_WIDTH*0.1;
void PerspectiveMode()										// Set Up A Perspective View
{


	// Enter into our projection matrix mode
	glMatrixMode( GL_PROJECTION );							

	// Pop off the last matrix pushed on when in projection mode (Get rid of ortho mode)
	glPopMatrix();											

	// Go back to our model view matrix like normal
	glMatrixMode( GL_MODELVIEW );							

	// We should be in the normal 3D perspective mode now
}

void OrthoMode(int left, int top, int right, int bottom)
{

	// Switch to our projection matrix so that we can change it to ortho mode, not perspective.
	glMatrixMode(GL_PROJECTION);						

	// Push on a new matrix so that we can just pop it off to go back to perspective mode
	glPushMatrix();									

	// Reset the current matrix to our identify matrix
	glLoadIdentity();								

	//Pass in our 2D ortho screen coordinates.like so (left, right, bottom, top).  The last
	// 2 parameters are the near and far planes.
	glOrtho( left, right, bottom, top, 0, 1 );	

	// Switch to model view so that we can render the scope image
	glMatrixMode(GL_MODELVIEW);								

	// Initialize the current model view matrix with the identity matrix
	glLoadIdentity();										
}
void loadhudtexture(){
	CreateTexture(hudtexture[0],"Resources/textures/contributionhud.bmp");
	CreateTexture(hudtexture[1],"Resources/textures/GREEN.bmp");//green
	CreateTexture(hudtexture[2],"Resources/textures/BLUE.bmp");//blue
	CreateTexture(hudtexture[3],"Resources/textures/RED.bmp");//red
	CreateTexture(hudtexture[4],"Resources/textures/controls.bmp");
	CreateTexture(hudtexture[5],"Resources/textures/WHITE.bmp");//WHITE
	ishudtextureloaded=true;

}


void drawhud(GVersion &version, int versionnum){
	OrthoMode(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);						
	if(!ishudtextureloaded)
		loadhudtexture();

	glBindTexture(GL_TEXTURE_2D, hudtexture[5]);//white background
	glBegin(GL_QUADS);
	// Display the top left point of the 2D image
	glTexCoord2f(0,1);	glVertex2f(0, 0);

	// Display the bottom left point of the 2D image
	glTexCoord2f(1,1);	glVertex2f(0, SCREEN_HEIGHT/8);

	// Display the bottom right point of the 2D image
	glTexCoord2f(1,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT/8);

	// Display the top right point of the 2D image
	glTexCoord2f(0,0);	glVertex2f(SCREEN_WIDTH, 0);
	// Stop drawing 

	glEnd();



	//jimmy
	glBindTexture(GL_TEXTURE_2D, hudtexture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);	glVertex2f(0, SCREEN_HEIGHT*.05);
	glTexCoord2f(1,1);	glVertex2f(0, SCREEN_HEIGHT*.09);
	glTexCoord2f(1,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT*.09);
	glTexCoord2f(0,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT*.05);
	glEnd();
	//anmol
		glBindTexture(GL_TEXTURE_2D, hudtexture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);	glVertex2f(0, 0);
	glTexCoord2f(1,1);	glVertex2f(0, SCREEN_HEIGHT*.049);
	glTexCoord2f(1,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT*.049);
	glTexCoord2f(0,0);	glVertex2f(SCREEN_WIDTH, 0);
	glEnd();
	//shirley
		glBindTexture(GL_TEXTURE_2D, hudtexture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);	glVertex2f(0, SCREEN_HEIGHT*.12);
	glTexCoord2f(1,1);	glVertex2f(0, SCREEN_HEIGHT*.09);
	glTexCoord2f(1,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT*.09);
	glTexCoord2f(0,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT*.12);
	glEnd();

	// mask
	glBlendFunc(GL_DST_COLOR,GL_ZERO);
	glEnable(GL_BLEND);	
	glBindTexture(GL_TEXTURE_2D, hudtexture[0]);



	glBegin(GL_QUADS);
	// Display the top left point of the 2D image
	glTexCoord2f(0,1);	glVertex2f(0, 0);

	// Display the bottom left point of the 2D image
	glTexCoord2f(1,1);	glVertex2f(0, SCREEN_HEIGHT/8);

	// Display the bottom right point of the 2D image
	glTexCoord2f(1,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT/8);

	// Display the top right point of the 2D image
	glTexCoord2f(0,0);	glVertex2f(SCREEN_WIDTH, 0);
	// Stop drawing 

	glEnd();
	glDisable(GL_BLEND);
	
	//hud
	glBindTexture(GL_TEXTURE_2D, hudtexture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);	glVertex2f(0, SCREEN_HEIGHT*.8);
	glTexCoord2f(1,1);	glVertex2f(0, SCREEN_HEIGHT);
	glTexCoord2f(1,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	glTexCoord2f(0,0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT*.8);
	glEnd();


	glDisable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);

	// Let's set our mode back to perspective 3D mode.  None of this archaic 2D stuff :)
	PerspectiveMode();
}

