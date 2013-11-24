#ifndef _HUD_H
#define _HUD_H

// This class contains methods for the Heads Up Display

#include "main.h"
#include "vector.h"
#include <sstream>

void drawhud(GVersion &version, int versionnum);
void PerspectiveMode();
void OrthoMode(int left, int top, int right, int bottom);
void loadhudtexture();

#endif