#include "Model.h"

using namespace std;

GPackage GVersion::searchPackage(string pn) {
	foreach(package,childPackages,vector<GPackage>) {
		if (package->packageName == pn) return *package;
	}
	return GPackage(-1);
}

GClass GPackage::searchClass(string cn) {
	foreach(gclass,childClasses,vector<GClass>) {
		if (gclass->className == cn) return *gclass;
	}
	return GClass(-1);
}

GMethod GClass::searchMethod(string mn) {
	foreach(method,childMethods,vector<GMethod>) {
		if (method->methodName == mn) return *method;
	}
	return GMethod(-1);
}

