#ifndef _GITLOGPARSER_
#define _GITLOGPARSER_

#include "Model.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex> //regular expression
#include "string.h"
class GitlogParser {

public:
	GitlogParser() {};
	~GitlogParser() {};


	// parse a file and write the output in the vectors
	bool glparse(GVersion &version);


};

#endif
