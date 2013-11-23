

#ifndef _GITLOGPARSER_
#define _GITLOGPARSER_

#include "Model.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class GitlogParser {

public:
	GitlogParser() {};
	~GitlogParser() {};


	// parse a file and write the output in the vectors
	int glparse(GVersion &version);


};

#endif

