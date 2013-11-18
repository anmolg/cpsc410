#include "Model.h"

using namespace std;



string printSpaces(int n){
	if (n==0) return " ";
	return " " + printSpaces(n-1);
}

int GVersion::searchPackage(string pn) {
	for(int i = 0; i < childPackages.size(); i++) {
		if (childPackages[i].packageName == pn) return i;
	}
	return -1;
}

void printMethods(GClass gc) {
	int size = gc.childMethods.size();
	cout << "(CODE-YUGIOH) size of methods is : " << size << endl;
	for (int j=0; j < size ; j++) {
		cout << "         " << gc.childMethods[j].methodName << endl;
	}
}

void printPackages(GPackage gp, int stop){
	int size = gp.childClasses.size();
	for (int j=0; j < size ; j++) {
		cout << "      " << gp.childClasses[j].className << endl;
		if (stop > CLASS)
			printMethods(gp.childClasses[j]);
	}
}

void GVersion::printVersion(int stop) {
	cout << "Version" << endl;
	for (int i=0; i < childPackages.size() ; i++){
		cout << "   " << childPackages[i].packageName << endl;
		if (stop > PACKAGE) {
			printPackages(childPackages[i],stop);

		}
	}
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

