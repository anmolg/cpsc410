#include <iostream>
#include <string>
#include "Model.h"
#include "XMLParser.h"

using namespace std;

int main() {
 int n;
GVersion version = GVersion(0);
 XMLParser xmlParser = XMLParser();
 for(int i=1;i<10;i++) {
	xmlParser.parse(i,version);
 }
 version.printVersion(METHOD); // enum { PACKAGE , CLASS , METHOD } defined in Model.h;
// xmlParser.parse("2",version);
 //cout<< version.childPackages[0].packageName<<endl;

 cin >> n;
 return 0;
}