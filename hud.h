#ifndef _HUD_H
#define _HUD_H

#include "main.h"
#include "vector.h"
#include "glut.h"
#include <sstream>

void drawhud(GVersion &version, int versionnum);
void PerspectiveMode();
void OrthoMode(int left, int top, int right, int bottom);
void loadhudtexture();

#endif