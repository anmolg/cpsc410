#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "GalaxyModel.h"
#include <math.h>

#define STAR_RADIUS 7
#define PLANET_RADIUS 0.5
#define PLANET_DISTANCE 30
#define MOON_RADIUS 0.5
#define MOON_DISTANCE 0.5
#define STAR_DISTANCE 40
#define MOON_BASE_ORBIT_SPEED 3.0 
#define PLANET_BASE_ORBIT_SPEED 1.0 
#define END_TIMER 150.0

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
	CreateTexture(galaxy_texture[3],"Resources/textures/ModelSun.bmp");
	CreateTexture(galaxy_texture[4],"Resources/textures/UISun.bmp");
	CreateTexture(galaxy_texture[5],"Resources/textures/TransactionsSun.bmp");
	CreateTexture(galaxy_texture[6],"Resources/textures/JDBCSun.bmp");
	CreateTexture(galaxy_texture[7],"Resources/textures/GreenMoon.bmp");
}

// draw red particles for burning moons when they are created
void drawBurningMoon() {
	for(int i = 0; i < MAX_PARTICLES; ++i)
	{
		gParticles[i].render();
		gParticles[i].process(dt);
	}

	glPushMatrix();
	glRotatef(180,0,1,0);
	for(int i = 0; i < MAX_PARTICLES; ++i)
	{
		gParticles[i].render();
		gParticles[i].process(dt);
	}
	glPopMatrix();
}

// Draw Yellow moons
void drawYellowBurningMoon() {
	for(int i = 0; i < MAX_PARTICLES; ++i)
	{
		gParticles2[i].render();
		gParticles2[i].process(dt);
	}

	glPushMatrix();
	glRotatef(180,0,1,0);
	for(int i = 0; i < MAX_PARTICLES; ++i)
	{
		gParticles2[i].render();
		gParticles2[i].process(dt);
	}
	glPopMatrix();
}

void drawSphere(float sphereRadius, float orbitRadius, float orbitSpeed, CelestialType type, int& psize)
{

	glEnable(GL_TEXTURE_2D);
	GLUquadricObj *pObj = gluNewQuadric();									// Push on a new matrix scope
	gluQuadricDrawStyle(pObj, GLU_FILL);
	gluQuadricTexture(pObj, 1);												// This turns on texture coordinates for our Quadrics
	gluQuadricNormals(pObj, GLU_SMOOTH);

	if (psize < END_TIMER) psize++;

	// Binds the texture for the stars based on the package name
	if (type == STAR){
		if (currentPackageName == "ui"){
		glBindTexture(GL_TEXTURE_2D, galaxy_texture[4]);}
		if (currentPackageName == "transactions"){
		glBindTexture(GL_TEXTURE_2D, galaxy_texture[5]);}
		if (currentPackageName == "model"){
		glBindTexture(GL_TEXTURE_2D, galaxy_texture[3]);}
		if (currentPackageName == "jdbc"){
		glBindTexture(GL_TEXTURE_2D, galaxy_texture[6]);}
	}
	// Binds the texture for the moons
	else if (type == MOON){
		// If the moon is just created then we bind green moon texture, else bind the normal moon texture
		if (psize < END_TIMER) glBindTexture(GL_TEXTURE_2D, galaxy_texture[7]);
		else glBindTexture(GL_TEXTURE_2D, galaxy_texture[1]);
	}
	// Binds the texture for the planets
	else if (type == PLANET){
		if (psize < END_TIMER) glBindTexture(GL_TEXTURE_2D, galaxy_texture[7]);
		else glBindTexture(GL_TEXTURE_2D, galaxy_texture[2]);
	}	

	glRotatef(orbitSpeed*g_time*60,0,1,0);	// Animates orbital rotation
	glTranslatef(orbitRadius,0,0);			// Translates the celestial object to it's location
	glPushMatrix();
	glRotatef(60*g_time, 0, -1, 0);			// Rotate the sphere around itself to produce self-rotation

	float sfactor = psize/END_TIMER;		
	glScalef(sfactor,sfactor,sfactor);		// Animation for increasing the size of planets when they are created

	gluSphere(pObj, sphereRadius, 24, 24);	

	glPopMatrix();
}


// Draws the moons which represent methods.
void drawMethod(GMethod& gm, int index,float p_radius) {
	// checking whether the moon should be displayed
	// displays when creationTime <= commitNumber < endTime
	if (commitNumber < gm.creationTime) return;
	if (commitNumber >= gm.endTime) return;
	glColor3f(1,1,1);

	glRotatef(gm.angle,1,0,0); // angle of rotation.
	
	glPushMatrix();

	drawSphere(	MOON_RADIUS,
		p_radius + index*MOON_DISTANCE,
		MOON_BASE_ORBIT_SPEED/sqrt((double) index),
		MOON,
		gm.psize); 
	if (gm.duplications[(int) min(commitNumber,gm.duplications.size()-1)]) {
		// This is when we encounter a method containing duplicate code
		// If it is newly created then draw it with red particles
		// otherwise display yellow particles
		if (gm.p_timer < END_TIMER) { gm.p_timer++;drawBurningMoon();}
		else drawYellowBurningMoon();
		
	}
	glPopMatrix();
}


// Draws planets which represent classes
void drawClass(GClass& gc,int index) {
	if (commitNumber<gc.creationTime) return;

	glColor3f(0,0,1); 
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