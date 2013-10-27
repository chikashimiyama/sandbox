#include <iostream>
#include <fstream>
#include <string>
#include "tinyxml2.h"

int main()
{
    using namespace tinyxml2;
    using namespace std;
    
    ifstream ifs("sample.xml");
    string xmlString;
    
    if (ifs.is_open())
    {
        while ( ifs.good() )
        {
            string str;
            getline (ifs,str);
            xmlString.append(str);
        }
        ifs.close();
    }
    
    XMLDocument xml;
    xml.Parse(xmlString.c_str());
    xml.Print();

}

