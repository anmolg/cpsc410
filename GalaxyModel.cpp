#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "GalaxyModel.h"
#include <math.h>

#define STAR_RADIUS 7
#define PLANET_RADIUS 0.5
#define PLANET_DISTANCE 30
#define MOON_RADIUS 0.5
#define MOON_DISTANCE 0.5
#define STAR_DISTANCE 30
#define MOON_BASE_ORBIT_SPEED 3.0 
#define PLANET_BASE_ORBIT_SPEED 1.0 

float dt = 1.0f / 200.0f;
UINT galaxy_texture[50];

string currentPackageName;

// Sets the star's location in a linear fashion.
void setStarLocation(int index) {
	if (index == 4) return;
	glTranslatef(0,(-1.5 + index)*STAR_DISTANCE,0);
	return;
}

// Loads the textures 
void loadgalaxytextures(){
	CreateTexture(galaxy_texture[0],"Resources/textures/ModelSun.bmp");
	CreateTexture(galaxy_texture[1],"Resources/textures/Moon.bmp");
	CreateTexture(galaxy_texture[2],"Resources/textures/Planet.bmp");
}

// 
void drawBurningMoon() {
	for(int i = 0; i < MAX_PARTICLES; ++i)
	{
		gParticles[i].render();
		gParticles[i].process(dt);
	}
}

void drawSphere(float sphereRadius, float orbitRadius, float orbitSpeed, CelestialType type, int& psize)
{

	glEnable(GL_TEXTURE_2D);
	GLUquadricObj *pObj = gluNewQuadric();									// Push on a new matrix scope
	gluQuadricDrawStyle(pObj, GLU_FILL);
	gluQuadricTexture(pObj, 1);						// This turns on texture coordinates for our Quadrics
	gluQuadricNormals(pObj, GLU_SMOOTH);

	if (type == STAR){
		if (currentPackageName == "ui"){}
		if (currentPackageName == "transactions"){}
		if (currentPackageName == ".."){}
		if (currentPackageName == "ui"){}
		glBindTexture(GL_TEXTURE_2D, galaxy_texture[0]);	
	}
	else if (type == MOON){
		glBindTexture(GL_TEXTURE_2D, galaxy_texture[1]);}	
	else if (type == PLANET){
		glBindTexture(GL_TEXTURE_2D, galaxy_texture[2]);}	

	glRotatef(orbitSpeed*g_time*60,0,1,0);	
	glTranslatef(orbitRadius,0,0);
	glPushMatrix();
	glRotatef(60*g_time, 0, 1.0, 0);			// Rotate the sphere around itself to produce the spin

	float sfactor = psize/100.0;
	glScalef(sfactor,sfactor,sfactor);
	if (psize < 100) {
		glColor3f(0,1,0);
		psize++;
	}

	gluSphere(pObj, sphereRadius, 24, 24);

	glPopMatrix();
}

void drawMethod(GMethod& gm, int index,float p_radius) {
	// checking whether the moon should be displayed
	// displays when creationTime <= commitNumber < endTime
	if (commitNumber < gm.creationTime) return;
	if (commitNumber >= gm.endTime) return;
	glColor3f(1,1,1);
	//int randomAngle = rand()%360; // THIS DID NOT WORK BECUZ IT GENERATES RANDOM STUFF EVERY TIME
	//float randomX = rand()%100 / 100.0;
	//float randomZ = rand()%100/100.0;
	glRotatef(index*60,1,0,0); // arbitrary angles of rotation.
	glPushMatrix();

	drawSphere(	MOON_RADIUS,
		p_radius + index*MOON_DISTANCE,
		MOON_BASE_ORBIT_SPEED/sqrt((double) index),
		MOON,
		gm.psize); // Last parameter just for testing
	if (gm.duplications[(int) min(commitNumber,gm.duplications.size()-1)]) {
		if (gm.p_timer < 60) { glColor3f(1,0,0); gm.p_timer++;}
		else glColor3f(1,1,0);
		drawBurningMoon();
	}
	glPopMatrix();
}

void drawClass(GClass& gc,int index) {
	if (commitNumber<gc.creationTime) return;

	glColor3f(0,0,1); // TODO : set colour corresponding to author commits.
	int sizeIndex = (int) min(commitNumber,gc.size.size()-1);
	if (gc.size[sizeIndex] == 0) return;
	float radius = PLANET_RADIUS + pow((double)gc.size[sizeIndex]/20,(double)1/3);
	//the volume propotional to line of code in a class, there for the radius is cube root
	drawSphere( radius,
		(radius/2) + index*PLANET_DISTANCE,
		PLANET_BASE_ORBIT_SPEED/sqrt((double) index),
		PLANET,
		gc.psize); // Last parameter is just for testing

	int i= 1;
	foreach(gmethod,gc.childMethods,vector<GMethod>) {
		glPushMatrix();
		drawMethod(*gmethod,i,radius);
		glPopMatrix();
		i++;
	}
}

void drawPackage(GPackage& gp,int p_index) {
	if(commitNumber < gp.creationTime) return;
	setStarLocation(p_index);				// set star location
	glColor3f(1,0.84,0);

	currentPackageName = gp.packageName;
	drawSphere(STAR_RADIUS,0,0,STAR,gp.psize);

	int index = 1;
	foreach(gclass,gp.childClasses,vector<GClass>) {
		glPushMatrix();
		drawClass(*gclass,index);
		glPopMatrix();
		index++;
	}

}