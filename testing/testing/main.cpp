#include <iostream>
#include <string>
#include "Model.h"
#include "XMLParser.h"

using namespace std;

int main() {
 int n;
GVersion version = GVersion(0);
 XMLParser xmlParser = XMLParser();
 xmlParser.parse(1,version);
 cout<<"0th package: "<<version.childPackages[0].packageName<<" 0th class: "<<version.childPackages[0].childClasses[0].childMethods[1].methodName<<endl;
 cout<<"~~"<<version.childPackages[0].childClasses[0].className<<endl;
 if(version.childPackages[0].childClasses[0].childMethods[0].methodName=="insertBorrowerType")
	 cout<<"Kenny needs Jimmy's phone"<<endl;
// xmlParser.parse("2",version);
 //cout<< version.childPackages[0].packageName<<endl;

 cin >> n;
 return 0;
}