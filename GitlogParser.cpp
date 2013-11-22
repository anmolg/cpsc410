#include "GitlogParser.h"
using namespace std;

void gpreparse(GVersion &version);
bool grealParse(	int filename);
void gupdate(GVersion &version, int versionNumber);
//void postparse(GVersion &version, int versionNumber);


string toString(double number);
//vector<GClass> tempClasses;
//vector<GMethod> tempMethods;
//vector<GPackage> tempPackages;
int versionNumber = 0;
bool GitlogParser::glparse(int filename, GVersion &version){
	// clear the temp vectors at the start of parsing.
	//tempClasses.clear();
	//tempPackages.clear();

	// if version is not empty, do parsing preparations.
	gpreparse(version);
	grealParse(filename);
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

int ggetNumber(string str, string keyword)
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

		}
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
vector<string> ggetGClassName(string str){
	vector<string> result(2,"");//default case
	int i =str.size();
	if (i>16){
		int cNameLength=0,pNameLength=0;	//length of class name and package name
		if ((str.substr(0,2) !="	c" )&&(str.substr(str.size()-5)==".java" )){
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
			//cout<<result[0]<<endl;
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
			//cout<<result[1]<<endl;

		};
	}
	return result;
}
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
	else if(str.substr(index,keyword.size()+3)=="</"+keyword+">")
		return -1;//triger finish element
	return 0;//default
}

bool grealParse(int filename) //filename is the version number
{	string line, targetString, s;
	s = toString(filename);
	//cout <<s.c_str()<<endl;
	ifstream file (s.c_str());

	bool isCheckingFile = false;	// file lines trigger
	bool isCheckingMethod = false;	// method lines trigger
	bool isCheckingClone = false;	// clone lines trigger
	bool authorAnmol = false;
	bool authorJimmy = false;
	bool authorShirley = false;

	if (file.is_open())
	{
		int iClass = 0;
		GClass tempC;
		GMethod tempM;
		//GClone tempCl;
		while ( file.good() )
		{
			getline (file,line);
			if (gflagTrigger(line, "Author: Anmol")==1){
				authorAnmol = true;
				authorJimmy = false;
				authorShirley = false;
				versionNumber++;
				//tempC = GClass( filename);
				//tempC.alive = true;
			}
			else if(gflagTrigger(line, "Author: Jimmy")==-1){
				authorAnmol = false;
				authorJimmy = true;
				authorShirley = false;
				versionNumber++;
				//isCheckingFile =false;
				//tempClasses.push_back (tempC);
			}

			else if (gflagTrigger(line, "Author: xueqixu")==1){
				authorAnmol = false;
				authorJimmy = false;
				authorShirley = true;
				versionNumber++;
				//isCheckingMethod =true;
				//tempM= GMethod( filename);
				//tempM.alive =true;

			}
			/*
			else if(flagTrigger(line,"METHOD")==-1){
				isCheckingMethod = false;
				tempMethods.push_back(tempM);
			}
			else if(flagTrigger(line,"CLONE")==1){
				isCheckingClone = true;
				//tempCl=GClone();
			}
			*/
			//-----------------------parse class stuff---------------------------
			if(authorAnmol){
				if (ggetGClassName(line)[0] != ""){
					string currentClassName = ggetGClassName(line)[0];
					for (int i = 0; i < GVersion(versionNumber).childPackages.size(); i++) {
						for (int j = 0; j < GVersion(versionNumber).childPackages[i].childClasses.size(); j++) {
							if (GVersion(versionNumber).childPackages[i].childClasses[j].className == currentClassName) {
								vector<Authors> tempAuthor = GVersion(versionNumber).childPackages[i].childClasses[j].authors;
								GVersion(versionNumber).childPackages[i].childClasses[j].authors[versionNumber].author_a++; // finding the corresponding vector to the versionNumber, and updating it by the number
								//int anmolCount = tempAuthor[versionNumber].author_a;
								//int jimmyCount = tempAuthor[versionNumber].author_j;
								//int shirleyCount = tempAuthor[versionNumber].author_s;
								//anmolCount++;
								//Authors tAuthor;
								//tAuthor.author_a = anmolCount;
								//tAuthor.author_j = jimmyCount;
								//tAuthor.author_s = shirleyCount;
								//GVersion(versionNumber).childPackages[i].childClasses[j].authors.push_back(tAuthor);							
							}
						}
						
					}
					
					//vector<string> path=getGClassName(line);
					//tempC.className=path[0];// the 0th elemet of the return value will be the class name
					//tempC.parentPackageName=path[1];// the first element will be package name				}
				}
			}
			else if(authorJimmy){
				if (ggetGClassName(line)[0] != ""){
					string currentClassName = ggetGClassName(line)[0];
					for (int i = 0; i < GVersion(versionNumber).childPackages.size(); i++) {
						for (int j = 0; j < GVersion(versionNumber).childPackages[i].childClasses.size(); j++) {
							if (GVersion(versionNumber).childPackages[i].childClasses[j].className == currentClassName) {
								vector<Authors> tempAuthor = GVersion(versionNumber).childPackages[i].childClasses[j].authors;
								GVersion(versionNumber).childPackages[i].childClasses[j].authors[versionNumber].author_j++; // finding the corresponding vector to the versionNumber, and updating it by the number
								//int anmolCount = tempAuthor[versionNumber].author_a;
								//int jimmyCount = tempAuthor[versionNumber].author_j;
								//int shirleyCount = tempAuthor[versionNumber].author_s;
								//anmolCount++;
								//Authors tAuthor;
								//tAuthor.author_a = anmolCount;
								//tAuthor.author_j = jimmyCount;
								//tAuthor.author_s = shirleyCount;
								//GVersion(versionNumber).childPackages[i].childClasses[j].authors.push_back(tAuthor);							
							}
						}
						
					}
					
					//vector<string> path=getGClassName(line);
					//tempC.className=path[0];// the 0th elemet of the return value will be the class name
					//tempC.parentPackageName=path[1];// the first element will be package name				}
				}
			}
			else if(authorShirley){
				if (ggetGClassName(line)[0] != ""){
					string currentClassName = ggetGClassName(line)[0];
					for (int i = 0; i < GVersion(versionNumber).childPackages.size(); i++) {
						for (int j = 0; j < GVersion(versionNumber).childPackages[i].childClasses.size(); j++) {
							if (GVersion(versionNumber).childPackages[i].childClasses[j].className == currentClassName) {
								vector<Authors> tempAuthor = GVersion(versionNumber).childPackages[i].childClasses[j].authors;
								GVersion(versionNumber).childPackages[i].childClasses[j].authors[versionNumber].author_s++; // finding the corresponding vector to the versionNumber, and updating it by the number
								//int anmolCount = tempAuthor[versionNumber].author_a;
								//int jimmyCount = tempAuthor[versionNumber].author_j;
								//int shirleyCount = tempAuthor[versionNumber].author_s;
								//anmolCount++;
								//Authors tAuthor;
								//tAuthor.author_a = anmolCount;
								//tAuthor.author_j = jimmyCount;
								//tAuthor.author_s = shirleyCount;
								//GVersion(versionNumber).childPackages[i].childClasses[j].authors.push_back(tAuthor);							
							}
						}
						
					}
					
					//vector<string> path=getGClassName(line);
					//tempC.className=path[0];// the 0th elemet of the return value will be the class name
					//tempC.parentPackageName=path[1];// the first element will be package name				}
				}
			}
			//--------------------parse clone stuff--------------------------------
			
		}


		//---------------------parse duplication stuff-------------------------
		//todo
	};
	//cout<<"hello "<<tempClasses[0].creationTime<<endl;
	//cout<<"hi "<<tempMethods[1].methodName<<endl;
	file.close();
	return true;
}



void gpreparseClass(GClass &c){
	c.alive =false;
	for (int i= 0; i<c.childMethods.size();i++){
		//preparseMethod(c.childMethods[i]);
		Authors temp;
		temp.author_a = 0;
		temp.author_j = 0;
		temp.author_s = 0;

		for (int j = 0; j < 123; j++) {
			c.authors.push_back(temp); // 123 commits, so pushing back a vector for each value
		}

	}
}

void gpreparsePackage(GPackage &p){
	p.alive =false;
	for (int i= 0; i<p.childClasses.size();i++){
		gpreparseClass(p.childClasses[i]);
	}
}

void gpreparse(GVersion &v){
	for (int i= 0; i<v.childPackages.size();i++){
		gpreparsePackage(v.childPackages[i]);
	}
}

/*
void update(GVersion &v, int versionNumber){

//update class data to version
	foreach (gclass, tempClasses, vector<GClass>){
		int indexP = v.searchPackage(gclass->parentPackageName);	//index of package
		int indexC = 0;												//index of class, default to 0 for case package don't exist
		//if package exists, then we update the class if it exists, and create new class if it does not.
		if (indexP>=0){			
			indexC = v.childPackages[indexP].searchClass(gclass->className);
		//if class exists
			if (indexC >=0){
				v.childPackages[indexP].childClasses[indexC].classID = gclass->classID;
				v.childPackages[indexP].childClasses[indexC].size.push_back(gclass->size[0]);// add the new snap shot of size
				v.childPackages[indexP].childClasses[indexC].alive = true;//this class is alive again
				for(int indexTM=0;indexTM<gclass->childMethods.size();indexTM++){
					bool updated =false;
					for(int indexM=0;indexM<v.childPackages[indexP].childClasses[indexC].childMethods.size();indexM++){
						if (v.childPackages[indexP].childClasses[indexC].childMethods[indexM].methodName == gclass->childMethods[indexTM].methodName){
							v.childPackages[indexP].childClasses[indexC].childMethods[indexM].methodID = gclass->childMethods[indexTM].methodID;//method exist, update
							v.childPackages[indexP].childClasses[indexC].childMethods[indexM].duplications.push_back(gclass->childMethods[indexTM].dTemp);//set the status of duplication of the newest version
							v.childPackages[indexP].childClasses[indexC].childMethods[indexM].alive=true;										//method is alive again
							updated = true;
						}
					}
					if (!updated){
						gclass->childMethods[indexTM].creationTime = versionNumber;
						gclass->childMethods[indexTM].id = gclass->childMethods[indexTM].newID();
						v.childPackages[indexP].childClasses[indexC].childMethods.push_back(gclass->childMethods[indexTM]);// new method, add it
						int indexM=v.childPackages[indexP].childClasses[indexC].childMethods.size()-1;
						for(int i=0;i<versionNumber;i++){		//for version that don't have this method, can't be duplicated
							v.childPackages[indexP].childClasses[indexC].childMethods[indexM].duplications.push_back(false);
						}
						v.childPackages[indexP].childClasses[indexC].childMethods[indexM].duplications.push_back(gclass->childMethods[indexTM].dTemp);//set the current duplication status
					}
				}
				v.childPackages[indexP].childClasses[indexC].alive = true;//this class a alive again
			}
		//class doesn't exist
			else {					
				for(int i=0; i<versionNumber-1; i++){				//this class' size for all previous versions are 0
					gclass->size.push_back(0);						//preserve the last slot for the real size
				}
				//// add method info
				//foreach(gmethod,gclass->childMethods,vector<GMethod>) {
				//	gmethod->creationTime = versionNumber;
				//	gmethod->id = gmethod->newID();
				//}
				gclass->size.push_back(gclass->size[0]);			//set the real size for this version
				gclass->creationTime = versionNumber;					
				v.childPackages[indexP].childClasses.push_back(*gclass);//add the new class to the package
				int indexC=v.childPackages[indexP].childClasses.size()-1;
				for(int indexM =0; indexM<v.childPackages[indexP].childClasses[indexC].childMethods.size(); indexM++){
					for(int i =0; i<versionNumber;i++){//for version that don't have this method, can't be duplicated
						v.childPackages[indexP].childClasses[indexC].childMethods[indexM].duplications.push_back(false);
					}
					v.childPackages[indexP].childClasses[indexC].childMethods[indexM].duplications.push_back(v.childPackages[indexP].childClasses[indexC].childMethods[indexM].dTemp);//set the current duplication status
				}
			}
			v.childPackages[indexP].alive = true;						// this package is now alive
		}
		
		//package don't exist, of course the class can't exist
		else{					
			v.childPackages.push_back(GPackage(versionNumber, gclass->parentPackageName));
			for(int i=0; i<versionNumber-1; i++){				//this class' size for all previous versions are 0
				gclass->size.push_back(0);						//preserve the last slot for the real size
			}
			gclass->size.push_back(gclass->size[0]);			//set the real size for this version
			gclass->creationTime=versionNumber;
			int indexP=v.childPackages.size()-1;
			v.childPackages[indexP].childClasses.push_back(*gclass);//add the new class to the package
			int indexC=v.childPackages[indexP].childClasses.size()-1;
			for(int indexM =0; indexM<v.childPackages[indexP].childClasses[indexC].childMethods.size(); indexM++){
				for(int i =0; i<versionNumber;i++){//for version that don't have this method, can't be duplicated
					v.childPackages[indexP].childClasses[indexC].childMethods[indexM].duplications.push_back(false);
				}
				v.childPackages[indexP].childClasses[indexC].childMethods[indexM].duplications.push_back(v.childPackages[indexP].childClasses[indexC].childMethods[indexM].dTemp);//set the current duplication status
			}
			v.childPackages[indexP].alive = true;
			v.childPackages[indexP].creationTime = versionNumber;
		}
	}
}
*/

/*
// convert number to string
string toString(double number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

*/
/*
void postparseClass(GClass &c, int versionNumber){
	if(c.alive ==false){
		c.size.push_back(0);
		if(c.endTime>versionNumber)
		{
			c.endTime = versionNumber;	//a class passed away at this time, amen!
		}
	}
	for (int i= 0; i<c.childMethods.size();i++)
		//postparseMethod(c.childMethods[i],versionNumber);
	
}

void postparsePackage(GPackage &p, int versionNumber){
	if(p.alive ==false){
		if(p.endTime>versionNumber)
			p.endTime=versionNumber;	//a package passed away at this time, amen!
	}
	for (int i= 0; i<p.childClasses.size();i++)
		postparseClass(p.childClasses[i],versionNumber);
}

void postparse(GVersion &v, int versionNumber){
	for (int i= 0; i<v.childPackages.size();i++)
		postparsePackage(v.childPackages[i], versionNumber);
};
*/

