#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "GalaxyModel.h"

#define STAR_RADIUS 2
#define PLANET_RADIUS 1
#define PLANET_DISTANCE 5
#define MOON_RADIUS 0.5
#define MOON_DISTANCE 1

UINT galaxy_texture[50];


void loadgalaxytextures(){
	CreateTexture(galaxy_texture[0],"Resources/textures/Sun.bmp");
	CreateTexture(galaxy_texture[1],"Resources/textures/Moon.bmp");
	CreateTexture(galaxy_texture[2],"Resources/textures/Planet.bmp");
}

void drawSphere(float sphereRadius, float orbitRadius, float orbitSpeed, CelestialType type)
{
	
	glEnable(GL_TEXTURE_2D);
	GLUquadricObj *pObj = gluNewQuadric();									// Push on a new matrix scope
	gluQuadricDrawStyle(pObj, GLU_FILL);
	gluQuadricTexture(pObj, 1);						// This turns on texture coordinates for our Quadrics
	gluQuadricNormals(pObj, GLU_SMOOTH);

	if (type == STAR){
	glBindTexture(GL_TEXTURE_2D, galaxy_texture[0]);	
}
else if (type == MOON){
	glBindTexture(GL_TEXTURE_2D, galaxy_texture[1]);}	
else {
	glBindTexture(GL_TEXTURE_2D, galaxy_texture[2]);}	

	glRotatef(orbitSpeed*g_time*60,0,1,0);	
	glTranslatef(orbitRadius,0,0);
	glPushMatrix();
	glRotatef(60*g_time, 0, 1.0, 0);			// Rotate the sphere around itself to produce the spin

	gluSphere(pObj, sphereRadius, 24, 24);					// Draw the sphere with a radius of 0.1 (smallest planet)
	glPopMatrix();
}

void drawMethod(GMethod gm, int index) {
	// checking whether the moon should be displayed
	// displays when creationTime <= commitNumber < endTime
	if (commitNumber < gm.creationTime) return;
	if (commitNumber >= gm.endTime) return;
	glColor3f(1,1,1);
	//int randomAngle = rand()%360; // THIS DID NOT WORK BECUZ IT GENERATES RANDOM STUFF EVERY TIME
	//float randomX = rand()%100 / 100.0;
	//float randomZ = rand()%100/100.0;
	glRotatef(index*60,1,0,0); // arbitrary angles of rotation.
	drawSphere(MOON_RADIUS,index*MOON_DISTANCE,3,MOON); // Last parameter just for testing
	glColor3f(1,0,0);
}

void drawClass(GClass gc,int index) {
	if (commitNumber<gc.creationTime) return;
	int a = gc.author_a; int j = gc.author_j; int s = gc.author_s;
	float total = a+j+s;
	glColor3f(a/total,j/total,s/total);
	drawSphere(PLANET_RADIUS,index*PLANET_DISTANCE,1+index,PLANET); // Last parameter is just for testing
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
	drawSphere(STAR_RADIUS,0,0,STAR);
	int index = 1;
	foreach(gclass,gp.childClasses,vector<GClass>) {
		glPushMatrix();
		drawClass(*gclass,index);
		glPopMatrix();
		index++;
	}

}