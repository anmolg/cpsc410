

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
	// Hey David, so my idea was to use one single version to include all our data
	// I changed the parameter from a vector of versions to just 1 version here. :-)
	// running nose, I might skip tmr's 410.
	bool parse(	const char *filename, GVersion *version);
};

#endif
