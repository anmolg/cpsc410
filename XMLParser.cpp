#include "XMLParser.h"
//#include <boost/tokenizer.hpp>
using namespace std;



/*helper function to prase a line of string into number, if the keyword matches
return -1 if fail to prase
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
bool XMLParser::parse(const char *filename, std::vector<GVersion> *Versions) 
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
		  cout<<"i'm "<< counter<<endl;
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