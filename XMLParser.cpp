#include "XMLParser.h"

using namespace std;

string getNumber(string str, string keyword)
{
    string new_str;
    size_t index = 0;
	int numLength =0;

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
				cout <<  index << endl;
				cout << str.size() << endl;
				while (numLength+index+2*keyword.size()+5 < str.size())
				{


					if (str[index+2+keyword.size()+numLength]!='<'){
						numLength++;
	//					cout<<"hi"<<numLength<<endl;
					}
					else
						break;
				}

			}
		}

	
	if (index < str.size())
        new_str = str.substr(index);

    return new_str;
}

/*bool XMLParser::parse(const char *filename, std::vector<GVersion> *versions) 
{
	ifstream in;
	in.open(filename, ios::in);
	if(!in.is_open()) {
		cout << "Error: XMLParser - could not open file " << filename << endl; 
		return false;
	}

	char currentLine[256];
	while(in.getline(currentLine,256)){
		string line(currentLine);
		cout << line << endl;
	}
}
*/
bool XMLParser::parse(const char *filename, std::vector<GVersion> *Versions) 
{
	string line, targetString;
	string s="output";
	ifstream file (s);
	if (file.is_open())
  {
    while ( file.good() )
    {
      getline (file,line);


	  targetString =getNumber(line,"FILEID");


    }

    file.close();

  }
return true;
}