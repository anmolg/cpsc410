#include "Model.h"

using namespace std;

int GVersion::searchPackage(string pn) {
	for(int i = 0; i < childPackages.size(); i++) {
		if (childPackages[i].packageName == pn) return i;
	}
	return -1;
}

int GPackage::searchClass(string cn) {
	for(int i = 0; i < childClasses.size(); i++) {
		if (childClasses[i].className == cn) return i;
	}
	return -1;
}

int GClass::searchMethod(string mn) {
	for(int i = 0; i < childMethods.size(); i++) {
		if (childMethods[i].methodName == mn) return i;
	}
	return -1;
}

