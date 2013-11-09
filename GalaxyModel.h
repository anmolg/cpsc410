#ifndef _GALAXYMODEL_
#define _GALAXYMODEL_

#include "Main.h"
#include "Model.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "GalaxyModel.h"
#include "Model.h"

#define STAR_RADIUS 2
#define PLANET_RADIUS 1
#define PLANET_DISTANCE 5
#define MOON_RADIUS 0.5
#define MOON_DISTANCE 1

enum CelestialType{STAR,PLANET,MOON};

void drawSphere(float sphereRadius, float orbitRadius, float orbitSpeed);

void drawMethod(GMethod gm, int index);

void drawClass(GClass gc,int index);

void drawPackage(GPackage gp);


//hold galaxy textures
void loadgalaxytextures();



#endif