#ifndef _GALAXYMODEL_
#define _GALAXYMODEL_

#include "Main.h"
#include "Model.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "GalaxyModel.h"
#include "Model.h"

// This is used to determine texturing for drawing spheres
enum CelestialType{STAR,PLANET,MOON,BURNING};

// Draws a sphere that takes in arguments for the radius
// the orbital radius
// the orbital speed (angular speed, degrees/time)
// psize is a timer for determining the radius of the sphere
void drawSphere(float sphereRadius, float orbitRadius, float orbitSpeed, int& psize);

// Draws Moons
void drawMethod(GMethod& gm, int index,float p_radius);

// Draws planets
void drawClass(GClass& gc,int index);

// Draws stars
void drawPackage(GPackage& gp,int index);

//holds galaxy textures
void loadgalaxytextures();



#endif