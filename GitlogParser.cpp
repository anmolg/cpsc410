#include "GitlogParser.h"
using namespace std;

void gpreparse(GVersion &version);
bool grealParse(GVersion &version);
void gupdate(GVersion &version, int versionNumber);
//void postparse(GVersion &version, int versionNumber);


string toString(double number);
//vector<GClass> tempClasses;
//vector<GMethod> tempMethods;
//vector<GPackage> tempPackages;
int versionNumber = 0;
	bool authorAnmol = false;
	bool authorJimmy = false;
	bool authorShirley = false;

bool GitlogParser::glparse(GVersion &version){
	// clear the temp vectors at the start of parsing.
	//tempClasses.clear();
	//tempPackages.clear();

	// if version is not empty, do parsing preparations.
	//gpreparse(version);
	grealParse(version);
	//update(version, filename);
	//postparse(version, filename);
	return true;
};


/*helper function to parse a line of XML, if the keyword matches
return:
target number OR
-1 if keyword doesn't match
input:
str: input line of XML file
*/
//getNumber("			<METHODNAME>_init_</METHODNAME>","METHODNAME") = -1
//getNumber("			<METHODFROMLINE>22</METHODFROMLINE>","METHODFROMLINE") = 22

/*get class name ANNNNND package name from FILEPATH
return:
a 2-element vector of string: ["fileName","pakageName"]
or if the line is not FILEPATH or not end with ".java": ["",""] 2 empty strings
str: input line of XML file

/*triger a flag for isReading an element of XML file ,for example
<FILE>		return 1:start 
...		return 0:in progress
</FILE>		return -1:end
*/

int gflagTrigger(string str, string keyword){
	size_t index = 0;
	int numLength =0;
	int result =-1;
	while (index < str.size())
	{
		if (isspace(str[index]))
			index++;
		else
			break;
	}
	if (str.substr(index, keyword.size()) == keyword)
		return 1;//triger start element
	//else if(str.substr(index,keyword.size()+3)=="</"+keyword+">")
		//return -1;//triger finish element
	return 0;//default
}

bool grealParse(GVersion &version) //filename is the version number
{	string line, targetString;
//	s = toString(filename);
	//cout <<s.c_str()<<endl;
	ifstream file ("gitlog.txt");


	if (file.is_open())
	{
		int iClass = 0;
		Authors tempA;
		while ( file.good() )
		{
			getline (file,line);
			if (gflagTrigger(line, "Author: Anmol")==1){
				authorAnmol = true;
				authorJimmy = false;
				authorShirley = false;
				versionNumber++;
				Authors oldAuthor = version.authors[versionNumber - 1];
				oldAuthor.author_a++;
				version.authors.push_back(oldAuthor);
				
			}
			else if(gflagTrigger(line, "Author: Jimmy")==-1){
				versionNumber++;
				Authors oldAuthor = version.authors[versionNumber - 1];
				oldAuthor.author_j++;
				version.authors.push_back(oldAuthor);
			}

			else if (gflagTrigger(line, "Author: xueqixu")==1){
				authorAnmol = false;
				authorJimmy = false;
				authorShirley = true;
				versionNumber++;
				
				Authors oldAuthor = version.authors[versionNumber - 1];
				oldAuthor.author_a++;
				version.authors.push_back(oldAuthor);
	
			}
			
		}
	}
	file.close();
	return true;
}
