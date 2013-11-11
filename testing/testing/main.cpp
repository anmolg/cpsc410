#include <iostream>
#include <string>
#include "Model.h"
#include "XMLParser.h"

using namespace std;

int main() {
 int n;
GVersion version = GVersion(1);
 XMLParser xmlParser = XMLParser();
 xmlParser.parse("outputt",version);

 cin >> n;
 return 0;
}