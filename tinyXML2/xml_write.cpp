#include <iostream>
#include "tinyxml2.h"

int main()
{
    using namespace tinyxml2;
    
    XMLDocument xml; // xml document
    XMLDeclaration* decl = xml.NewDeclaration(); //define a declaration (ver. encoding etc)
	decl->SetValue("xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"");
    xml.InsertEndChild(decl); // add declaration to document

    XMLElement* spatdif = xml.NewElement("spatdif"); //declare element
    xml.InsertEndChild(spatdif); // add element
    
    XMLElement* meta = xml.NewElement("meta"); //declare element
    spatdif->InsertEndChild(meta); // add element
    
    XMLElement* info = xml.NewElement("info"); //declare element
    meta->InsertEndChild(info); // add element

    XMLElement* annotation = xml.NewElement("annotation"); //declare element
    info->InsertEndChild(annotation); // add element

    XMLText* text = xml.NewText("this is a simple spatdif scene with 3 sources"); // declare text
    annotation->InsertEndChild(text); // add text to telement
    
    xml.Print();
    std::cout << "¥n";
    
}