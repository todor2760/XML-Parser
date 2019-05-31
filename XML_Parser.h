#ifndef XML_PARSER_H
#define XML_PARSER_H
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <TreeOfElements.h>
#include <Element.h>
using std::cout;
using std::endl;
using std::cin;
using std::string;

class XML_Parser
{
      public:
        bool IsOpened(){return myXmlFile.is_open();}
        void XML_Print(Element* parent_element,int depth);
        void CreateTree(Element* parent_element,int depth);
        bool SeekingInTheTree(Element* parent_element,int depth,Element* current_element,string id,bool found_match);
        Element SeekingInTheTree(Element* parent_element,int depth,string id,Element found_match,bool is_changing);
        void CreateUniqueIds(Element* parent_element,int depth);
        void SelectAttribute();
        void ChangeAttributeValue();
        void ChildrenAttributes();
        void GetText();
        void GetNChild();
        void DeleteAttribute();
        void AddNewInheritor();
        void OpenFile();
        void CloseFile();
        void SaveRecursiveFunc(Element* parent_element,int depth);
        void SaveFile(bool save_as);
    protected:

    private:
        std::string path;
        std::fstream myXmlFile;
        TreeOfElements tree_of_elements;
};

#endif // XML_PARSER_H
