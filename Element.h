#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include <vector>
#include <cstring>
#include <Attribute.h>

using std::string;
using std::vector;
class Element
{
    public:
        Element(){};
        Element(string name,string id,string text,
                vector<Attribute> attributes);
        Element(const Element& element_to_copy);
        Element& operator=(const Element& element_to_assign);
        string GetName()const{return name;}
        string GetId()const{return id;}
        void SetId(string id){this->id=id;}
        string GetText()const{return text;}
        vector<Attribute> GetAttributes()const{return attributes;}
        void SetAttributes(Attribute& attribute_to_add,int position){
             if(attributes.size()>position){
                attributes[position]=attribute_to_add;
             }
        }
        vector<Element*> GetChildrenElements()const{return children_elements;}
        void SetChildrenElements(Element* children_to_add){
             if(children_to_add!=nullptr){
                children_elements.push_back(children_to_add);
             }
        }
        ~Element();
    private:
        string name;
        string id;
        string text;
        vector<Attribute> attributes;
        vector<Element*> children_elements;
};

#endif // ELEMENT_H
