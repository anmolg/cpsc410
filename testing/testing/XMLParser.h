

#ifndef _XMLPARSER_
#define _XMLPARSER_

#include "Model.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex> //regular expression
#include "string.h"
class XMLParser {

public:
	XMLParser() {};
	~XMLParser() {};


	// parse a file and write the output in the vectors
	bool parse(	const char *filename, GVersion *version);


};

#endif
