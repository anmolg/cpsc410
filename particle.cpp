#include "particle.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include "main.h"
//#include "gl_obj.h"

// Default constructor -- Zero everything out
CParticle::CParticle()
{
	mSize = 0.0f;
	mLife = 0.0f;
	mAngle = 0.0f;
	
	// All other variables gets initialized with it's constructor
}

// Init the particle
bool CParticle::init(const CPos &p, const CVector &v, float lifeSpan, float s, float a, 
					 const char *texName)
{
	mPos = p; // Set the position
	mVel = v; // Set the velocity
	
	// Don't allow initialization of a "dead" particle 
	if(lifeSpan <= 0.0f)
		return false;
	
	mLife = lifeSpan; // Set the time, in seconds, the particle will remain alive
	
	// Size must be positive
	if(s <= 0.0f)
		return false;
		
	mSize = s; // Set the size
	mAngle = a; // Set the angle of texture UV rotation per second

	
	if(texName) // If a texture name was specified
		return mTexture.load(texName); // Load the texture
	else
		return true;
}

void CParticle::changeToYellow() {
		mTexture.load("particlesYellow.bmp"); // Load the texture
}

void CParticle::process(float dt)
{
	// If particle is dead, reset it's position
	if(isAlive() == false)
	{
		mLife = RAND(0.0f, 2.0f); // Make it alive again
		mPos = CPos(0,0,0); // Reposition to the emission point
			return;
	}		

	// Apply velocity
	mPos.x += mVel.x * dt;
	mPos.y += mVel.y * dt;
	mPos.z += mVel.z * dt;
		
	mLife -= dt; // Decrease particle's life span
	
}

void CParticle::render()
{
	// If particle isn't alive, then there is nothing to render
	if(isAlive() == false)
		return;
	
	// Can't render a particle that does not have a valid texture 
	if(mTexture.getId() == TEXTURE_NOT_LOADED)
		return;


	// Set the texture for rendering
	mTexture.select();
	
	glPushMatrix();
	
		// Move to the world position of where to draw the particle
		glTranslatef(mPos.x, mPos.y, mPos.z);
		
		float halfSize = mSize * 0.5f;
		// Draw the particle
		glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0, halfSize, 0.0f); // Top left vertex
			
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-halfSize, -halfSize, 0.0f); // Bottom left vertex
			
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(halfSize, -halfSize, 0.0f); // Bottom right vertex
		glEnd();
		
	glPopMatrix();

}
	
	
	
		
	
	
	
	
	
	
