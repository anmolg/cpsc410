

#ifndef _XMLPARSER_
#define _XMLPARSER_

#include "Model.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class XMLParser {

public:
	XMLParser() {};
	~XMLParser() {};

	// parse a file and write the output in the vectors
	bool parse(	const char *filename, std::vector<GPackage> *packages);
};

#endif
