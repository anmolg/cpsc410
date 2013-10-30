#include "XMLParser.h"
//#include <boost/tokenizer.hpp>
using namespace std;



/*helper function to prase a line of XML, if the keyword matches
return:
	target number OR
	-1 if keyword doesn't match
input:
	str: input line of XML file
*/
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
//				cout<<result<<endl;
			}
		}

	


//		cout<< "yoHO"<<result+100.0<<endl;
    return result;
}

/*get class name ANNNNND package name from FILEPATH
return:
	a 2-element vector of string: ["fileName","pakageName"]
	or if the line is not FILEPATH or not end with ".java": ["",""] 2 empty strings
str: input line of XML file

*/

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
<FILE>
	...
</FILE>
1:start 
0:in progress
-1:end
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
bool XMLParser::parse(const char *filename, GVersion *version) 
{
	string line, targetString;
	int result;
	int counter=100;
	string s="output";
	ifstream file (s);
	if (file.is_open())
  {
    while ( file.good() )
    {
      getline (file,line);
//	  if(line.substr(0,11).compare("<FILEID>")==0){
//	  keyString =line
	  if (flagTrigger(line,"FILE")==1){
		  counter =1;
		  cout<<"start file"<<endl;
	  }
	  else if(flagTrigger(line,"FILE")==0)
		  counter ++;
	  else if(flagTrigger(line,"FILE")==-1){
		  counter ++;
		  cout<<"end file"<<endl;
	  }
//		  cout<<"i'm "<< counter<<endl;
	  vector<string> dummy=getGClassName(line);
	  result =getNumber(line,"FILEID");
//	  if( result !=-1)
//	  cout<<result<<endl;
	  //	  		  cout<<line<<endl;
//		  cout<<getNumber(line, )<<endl;
    };

    file.close();

  }
return true;
}