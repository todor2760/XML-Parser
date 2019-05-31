#include <iostream>
#include <string>
#include <cstring>

#include <XML_Parser.h>
using namespace std;

int main()
{
    XML_Parser xml_parser;
    string command;
    cout<<"Type:\n'open' to open a xml file;\n'close' to close a xml file;\n'save' to save the file;\n'save_as'....;\n'exit' to exit the program"<<endl;
    cout<<endl<<"Type if a file is opened:\n'print' to print the information"<<endl;
    cout<<"'select' to print attribute value by given id and key"<<endl;
    cout<<"'assign_value' to change an attribute value by given id and key"<<endl;
    cout<<"'children_attributes' to print children attributes by given parent element id"<<endl;
    cout<<"'n_child'..."<<endl;
    cout<<"'get_text' type id and name of the element"<<endl;
    cout<<"'delete_attribute' type id and name of the attribute you want to delete"<<endl;
    cout<<"'add_inheritor' type it to add inheritor to element"<<endl;
    cin>>command;
    while(strcmp(command.c_str(),"exit")!=0){

        if(strcmp(command.c_str(),"print")==0&&xml_parser.IsOpened()){
              xml_parser.XML_Print(nullptr,0);
        }
        else if(strcmp(command.c_str(),"select")==0&&xml_parser.IsOpened()){
              xml_parser.SelectAttribute();
        }
        else if(strcmp(command.c_str(),"assign_value")==0&&xml_parser.IsOpened()){
              xml_parser.ChangeAttributeValue();
        }
        else if(strcmp(command.c_str(),"children_attributes")==0&&xml_parser.IsOpened()){
              xml_parser.ChildrenAttributes();
        }
        else if(strcmp(command.c_str(),"n_child")==0&&xml_parser.IsOpened()){
              xml_parser.GetNChild();
        }
        else if(strcmp(command.c_str(),"get_text")==0&&xml_parser.IsOpened()){
              xml_parser.GetText();
        }
        else if(strcmp(command.c_str(),"delete_attribute")==0&&xml_parser.IsOpened()){
              xml_parser.DeleteAttribute();
        }
        else if(strcmp(command.c_str(),"add_inheritor")==0&&xml_parser.IsOpened()){
              xml_parser.AddNewInheritor();
        }
        else if(strcmp(command.c_str(),"open")==0){
              if(!xml_parser.IsOpened()){
              xml_parser.OpenFile();
              }
              else{
              cout<<"the file is already opened"<<endl;
              }
        }
        else if(strcmp(command.c_str(),"close")==0){
              xml_parser.CloseFile();
              cout<<"Type open | close | exit | save | save as"<<endl;
        }
        else if(strcmp(command.c_str(),"save")==0){
              if(xml_parser.IsOpened()){
                xml_parser.SaveFile(false);
              }
              else{
                cout<<"there isnt a opened file"<<endl;
              }
        }
        else if(strcmp(command.c_str(),"save_as")==0){
              if(xml_parser.IsOpened()){
                xml_parser.SaveFile(true);
              }
              else{
                cout<<"there isnt a opened file"<<endl;
              }
        }
        else if(strcmp(command.c_str(),"exit")==0){
              xml_parser.CloseFile();
        }
        else{
              cout<<"Invalid command try again"<<endl;
        }
        cin>>command;
    }
}

