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
 if(version.childPackages[0].packageName=="testfile")
	 cout<<"Kenny needs Jimmy's phone"<<endl;
 version.printVersion(METHOD);
// xmlParser.parse("2",version);
 //cout<< version.childPackages[0].packageName<<endl;

 cin >> n;
 return 0;
}