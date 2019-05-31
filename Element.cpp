#include "Element.h"


Element::Element(string name,string id,string text,
                vector<Attribute> attributes)
{
    if(!name.empty()){
        this->name=name;
    }
    if(!id.empty()){
        this->id=id;
    }
    if(!text.empty()){
        this->text=text;
    }
    if(attributes.size()>0){
        this->attributes=attributes;
    }
}

Element::Element(const Element& element_to_copy):name(element_to_copy.name),id(element_to_copy.id),text(element_to_copy.text),attributes(element_to_copy.attributes){
    for(int i=0;i<element_to_copy.children_elements.size();i++){
        Element* tmp=new Element;
        tmp=element_to_copy.children_elements[i];
        children_elements.push_back(tmp);
    }
}

Element& Element::operator=(const Element& element_to_assign){
    name=element_to_assign.name;
    id=element_to_assign.id;
    text=element_to_assign.text;
    attributes=element_to_assign.attributes;
    for(int i=children_elements.size()-1;i>=0;i--){
        delete children_elements[i];
        children_elements.pop_back();
    }
    for(int i=0;i<element_to_assign.children_elements.size();i++){
        Element* tmp=new Element;
        tmp=element_to_assign.children_elements[i];
        children_elements.push_back(tmp);
    }
    return *this;
}
Element::~Element(){
    for(int i=children_elements.size()-1;i>=0;i--){
        std::cout<<children_elements[i]->GetName()<<children_elements[i]->GetId()<<std::endl;
        delete[] children_elements[i];
        children_elements.pop_back();
    }
}

