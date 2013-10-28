#include "XMLParser.h"

using namespace std;

bool XMLParser::parse(const char *filename, std::vector<GPackage> *packages) 
{
	ifstream in;
	in.open(filename, ios::in);
	if(!in.is_open()) {
		cout << "Error: XMLParser - could not open file " << filename << endl; 
		return false;
	}

	char currentLine[256];
	while(in.getline(currentLine,256)){
		string line(currentLine);
		cout << line << endl;
	}
}