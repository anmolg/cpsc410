#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdio.h>
#include "vector.h"
#include "gl_texture.h"


// Returns a random percent between 0 - 1
#define RAND_PERCENT() ((rand() & 0x7FFF) / ((float)0x7FFF))

// Returns a random number between (and including) "min" and "max"
// Assumes "min" < "max"
#define RAND(min, max) (min + (max - min) * RAND_PERCENT())

// The particle
class CParticle
{
	public:
		
		CParticle(); // Default constructor
		
		// This initializes a particle
		bool init(const CPos &pos, const CVector &vel, float lifeSpan, float size,
				  float angle = 0.0f, const char *texName = NULL);
		
		void process(float dt); // Moves the particle each frame
		void render(); // Renders the particle to screen
		void changeToYellow();
		// If the a particle's life is greater than zero, it's considered active
		// otherwise it's deactivate
		bool isAlive() { return (mLife > 0.0f); }
	
	private:
	
		CPos mPos; // World position
		CVector mVel; // Velocity
		
		int mColor; // ARGB color of particle
		float mSize; // Width/Height dimensions of the particle
		float mLife; // Life span of particle in seconds
		float mAngle; // Angle, in degrees, to rotate the texture's UVs every second
		
		CGLTexture mTexture; // The texture			 
};

#endif
