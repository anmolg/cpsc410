#include "XMLParser.h"
//#include <boost/tokenizer.hpp>
using namespace std;

void preparse(GVersion &version);
bool realParse(	const char *filename, GVersion &version);
void postparse();//todo

/*helper function to parse a line of XML, if the keyword matches
return:
target number OR
-1 if keyword doesn't match
input:
str: input line of XML file
*/
//getNumber("			<METHODNAME>_init_</METHODNAME>","METHODNAME") = -1
//getNumber("			<METHODFROMLINE>22</METHODFROMLINE>","METHODFROMLINE") = 22

int getNumber(string str, string keyword)
{
	string new_str;
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

	//get rid of empty space
	//------------------------------------
	//compare keyword
	if (index+keyword.size()+1<str.size()){
		if(str.substr(index+1,keyword.size())==keyword){
			//			cout <<  index << endl;
			//			cout << str.size() << endl;
			while (numLength+index+2*keyword.size()+5 < str.size())
			{


				if (str[index+2+keyword.size()+numLength]!='<'){
					numLength++;
					//					cout<<"hi"<<numLength<<endl;
				}
				else
					break;
			}
			new_str=str.substr(index+2+keyword.size(),numLength+1);
			//			cout<<new_str<<endl;  //search for keyword
			result =atoi(new_str.c_str());
			cout<<result<<endl;
		}
	}




	//		cout<< "yoHO"<<result+100.0<<endl;
	return result;
}

/*return a method name given an XML line,
or and empty string if that's a wrong line.
*/
// getMethodName("			<METHODNAME>_init_</METHODNAME>") = "_init_"

string getMethodName(string str){
	string result="";
	if ((str.substr(0,15)=="			<METHODNAME>" )&&(str.substr(str.size()-13)=="</METHODNAME>" )){
		result=str.substr(15,str.size()-28);
		//cout<<result<<endl;
	}
	return result;
}
/*get class name ANNNNND package name from FILEPATH
return:
a 2-element vector of string: ["fileName","pakageName"]
or if the line is not FILEPATH or not end with ".java": ["",""] 2 empty strings
str: input line of XML file

*/
//getGClassName("			<FILEPATH>C:\Users\Jimmy\Desktop\versions\TEST\testfile\ClerkFrame.java</FILEPATH>") = 
// vector<> = {"ClerkFrame","testfile"}
vector<string> getGClassName(string str){
	vector<string> result(2,"");//default case
	int i =str.size();
	if (i>16){
		int cNameLength=0,pNameLength=0;	//length of class name and package name
		if ((str.substr(0,13)=="			<FILEPATH>" )&&(str.substr(str.size()-16)==".java</FILEPATH>" )){
			int index =str.length() - 17;//search for class name
			while (i>index)
			{
				if (str[index]!='\\'){
					index--;
					cNameLength++;
				}
				else
					break;

			}
			result[0]=str.substr(index+1,cNameLength);
			cout<<result[0]<<endl;
			index =str.length() - 17 -cNameLength;//search for class name
			index--;
			while (i>index)
			{
				if (str[index]!='\\'){
					index--;
					pNameLength++;
				}
				else
					break;
			}
			result[1]=str.substr(index+1,pNameLength);
			cout<<result[1]<<endl;

		};
	}
	return result;
}
/*triger a flag for isReading an element of XML file ,for example
<FILE>		return 1:start 
...		return 0:in progress
</FILE>		return -1:end
*/

int flagTrigger(string str, string keyword){
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
	if (str.substr(index,keyword.size()+2)=="<"+keyword+">")
		return 1;//triger start element
	else if(str.substr(index,keyword.size()+3)=="</"+keyword+">")
		return -1;//triger finish element
	return 0;//default
}


bool XMLParser::parse(const char *filename, GVersion &version){
	//	preparse(version);

	realParse(filename, version);
	//postparse();//todo
	return true;
};


bool realParse(const char *filename, GVersion &version) 
{
	string line, targetString;
	//int result;			// for testing
	//int counter=0; 
	int versionNumber;			// file name
	ifstream file (filename);
	bool isCheckingFile = false;	// file lines trigger
	bool isCheckingMethod = false;	// method lines trigger
	vector<GPackage> newPackage;
	vector<GClass> newClass;
	vector<GMethod> newMethod;
	if (file.is_open())
	{
		vector <GClass> gClass;
		vector <GMethod> gMethod;
		int iClass = 0;
		int iClassCurrent = 0;
		while ( file.good() )
		{
			getline (file,line);
			if (flagTrigger(line,"FILE")==1){
				isCheckingFile =true;
				GClass tempC= GClass();
				tempC.creationTime =atoi(filename);	//dummy creation time update only if this value is less then the previous version(actually that will never happen)
				tempC.alive = true;
				gClass.push_back (tempC);

			}
			else if(flagTrigger(line,"FILE")==-1){
				isCheckingFile =false;
				//tempC->alive = false;
				iClass++;
			}

			else if (flagTrigger(line,"METHOD")==1){
				isCheckingMethod =true;
				GMethod tempM= GMethod();
				gMethod.push_back(tempM);
			}
			else if(flagTrigger(line,"METHOD")==-1){
				isCheckingMethod =false;
			}


			if(isCheckingFile){


				if( getNumber(line, "FILEID") > 0){		//file ID
					gClass[iClass].classID= getNumber(line, "FILEID"); // fileid
				}
				else if(getNumber(line, "FILELOC") > 0) {
					gClass[iClass].size = getNumber(line,"FILELOC"); // size
				}else if (getGClassName(line)[0] != ""){
					gClass[iClass].className = getGClassName(line)[0]; // size
					//todo create package
				}

			}

			vector<string> dummy=getGClassName(line);
			string ymmud =getMethodName(line);
			//result =getNumber(line,"FILEID");
			//	  if( result !=-1)
			//	  cout<<result<<endl;
			//	  		  cout<<line<<endl;
			//		  cout<<getNumber(line, )<<endl;
		};

		file.close();

	}
	return true;
}

void preparseMethod(GMethod &m){
	m.alive = false;
}

void preparseClass(GClass &c){
	c.alive =false;
	for (int i= 0; i<c.childMethods.size();i++){
		preparseMethod(c.childMethods[i]);
	}
}

void preparsePackage(GPackage &g){
	g.alive =false;
	for (int i= 0; i<g.childClasses.size();i++){
		preparseClass(g.childClasses[i]);
	}
}

void preparse(GVersion &v){
	for (int i= 0; i<v.childPackages.size();i++){
		preparsePackage(v.childPackages[i]);
	}
}