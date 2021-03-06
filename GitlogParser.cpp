// you will see EXTREME similarities to http://cs.dvc.edu/HowTo_Cparse.html
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>
#include "Model.h"
#include "GitlogParser.h"

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

	
int anmolTimes = 0;
int jimmyTimes = 0;
int shirleyTimes = 0;
int versionNumber = 0;

int GitlogParser::glparse(GVersion &version)
{
	Authors start;
	start.author_a = 0;
	start.author_j = 0;
	start.author_s = 0;

	version.authors.push_back(start);
  // create a file-reading object
  ifstream fin;
  fin.open("log.txt"); // open a file
  if (!fin.good()) 
    return 1; // exit if file not found
  
  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
    
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    
    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
    // parse the line
    token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
        if (!token[n]) break; // no more tokens
      }
    }
	if (token[1] != NULL) { 
		const char * tok;
		tok = token[1];
		const char * anmol = "Anmol";
		const char * jimmy = "Jimmy";
		const char * jimmyPart2 = "jimmy.gnahz";
		const char * jimmyPart3 = "jimmy-gnahz";
		const char * shirley = "xueqixu";
		int compAnmol = strcmp (tok, anmol);
		if (compAnmol == 0) {
			Authors old = version.authors[versionNumber];
			old.author_a++;
			version.authors.push_back(old);
			versionNumber++;
		}
		
		int compJimmy = strcmp (tok, jimmy);
		int compJimmyP = strcmp (tok, jimmyPart2);
		int compJimmyP2 = strcmp (tok, jimmyPart3);
		if (compJimmy == 0 || compJimmyP == 0 || compJimmyP2 == 0) {
			Authors old = version.authors[versionNumber];
			old.author_j++;
			version.authors.push_back(old);
			versionNumber++;
		}
		
		int compShirley = strcmp (tok, shirley);
		if (compShirley == 0) {
			Authors old = version.authors[versionNumber];
			old.author_s++;
			version.authors.push_back(old);
			versionNumber++;
		}
	}
	
	

  }

 return 0;
}