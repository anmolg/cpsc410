#ifndef _MODEL_
#define _MODEL_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GVersion {
public:
	GVersion(){}
	~GVersion(){}
private:
	int versionNumber;
	vector<GPackage> childPackages;
};

class GPackage {
public:
	GPackage(){}
	~GPackage(){}

private:
	int creationTime;
	int packageID;
	string packageName;
	vector<GClass> childClasses;

};

class GClass {
public:
	GClass(){}
	~GClass(){}
	GMethod searchMethod(string methodName);
	
private:
	vector<GMethod> childMethods;		// list of methods in the class
	string className;					
	int classID;						// generated by scorpio
	int creationTime;					// commit(/version) number when the class was added
	int size;							// number of lines
	// number of edits by each author to determine the RGB coloring
	int author_a;							// Anmol
	int author_s;							// Shirley (Xue Qi)
	int author_j;							// Jimmy
};

class GMethod {
public:

	GMethod() 
	{}
	~GMethod(){}

	int getCreationTime() {return creationTime;}
	int getEndTime(){}
	int setEndTime(int t){}

private:
	int creationTime;						// commit number where method was added		
	int endTime;							// commit number where method was deleted
	int duplicationID;						// an id to determine which two methods are duplicates
	int size;								// number of lines
	string methodName;
	int methodID;
	GClass parentClass;			
};

#endif