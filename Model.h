#ifndef _MODEL_
#define _MODEL_

////////////////////////////////////////////////////////////////////////

// This file contains classes used to model the galaxy

////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GVersion;
class GPackage;
class GClass;
class GMethod;

struct Authors {
	int author_a;							// Anmol
	int author_s;							// Shirley (Xue Qi)
	int author_j;							// Jimmy
};

enum {PACKAGE,CLASS,METHOD};				// This enum is for the method printVersions()

///////////////////////////////////////////////////////////////////////////

// helper function for iterating over std::vector<>
// it makes iterating over STL elements much easier
// instead of 
//
//		_type::iterator _var = _coll.begin();
//		for(; _var != _coll.end(); _var++) {
//			...
//		}
//
//	you can just use
//
//		foreach(_var, _coll, _type) {
//			...
//		}
#define foreach(_var, _coll, _type) \
	for (_type::iterator _var = _coll.begin(); \
         _var != _coll.end(); ++_var)

class GVersion {
public:
	GVersion(int vn){versionNumber = vn;}
	~GVersion(){}

	// return the index of package,
	//or -1 if we can't find it
	int searchPackage(string pn);

	// for visualization and debugging purposes, prints out the structure to console.
	void printVersion(int stop); 
	
	// Field Variables
	int versionNumber;
	vector<GPackage> childPackages;
	vector<Authors> authors;			// 125 entries, accumulative.
	bool alive;
};

class GPackage {
public:
	GPackage(int ct, string pn){creationTime = ct; packageName = pn;psize = 0;}
	GPackage(int ct){creationTime = ct; endTime =  2147483647;psize = 0;};
	~GPackage(){}
	// return the index of class,
	//or -1 if we can't find it
	int searchClass(string classname);

	// Field Variables:
	int creationTime;				// if creationTime = -1, then it's a dummy
	int endTime;					//  commit number where method was deleted, default to be infinity
	int packageID;					// might not use
	string packageName;
	vector<GClass> childClasses;
	bool alive;
	int psize; // an integer from 0 - 100 used for animating the growth of a planet/star/moon

};

class GClass {
public:
	GClass(){}
	GClass(int ct){creationTime = ct; endTime =  2147483647; psize = 0;}
	~GClass(){}

	// return the index of package,
	//or -1 if we can't find it
	//we don't handle overload methods
	int searchMethod(string methodName);

	vector<GMethod> childMethods;		// list of methods in the class
	string className;	
	string parentPackageName;
	int classID;						// generated by scorpio
	int creationTime;					// commit(/version) number when the class was added
	int endTime;						// commit number where method was deleted,default to be infinity
	vector<int> size;					// number of lines, the 0th element is a dummy
	// number of edits by each author to determine the RGB coloring
	// a value between 0 and 100
	int psize;					// Used in the animation, for shrinking and expanding the planets (has nothing to do with parsing)
	bool alive;
};

class GMethod {
public:

	GMethod(){}
	GMethod(int ct){creationTime = ct; 
				endTime = 2147483647;
				psize = 0;
				p_timer=0;
				angle = rand()%360;}
	~GMethod(){}
	int newID();							// 

	int creationTime;						// commit number where method was added		
	int endTime;							// commit number where method was deleted, default to be infinity
	vector<bool> duplications;	
	bool dTemp;								// used by xml parser, does this method has a duplication in this version
	string methodName;
	int methodID;			// generated by scorpio
	int id;					// generated by us
	int parentClassID;			
	bool alive;
	int psize;
	int p_timer;			// timer for particles
	int angle;				// angle between rotation plane and the x-z plane
	
};

#endif
