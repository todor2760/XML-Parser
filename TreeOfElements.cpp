#include "TreeOfElements.h"

Element* TreeOfElements::AddLeaf(Element* parent_element,
                                 Element* child_to_add){

     parent_element->SetChildrenElements(child_to_add);
     return child_to_add;
}

TreeOfElements::TreeOfElements(const TreeOfElements& tree_to_copy){
     for(int i=0;i<tree_to_copy.top_elements.size();i++){
        Element* tmp=new Element;
        tmp=tree_to_copy.top_elements[i];
        top_elements.push_back(tmp);
     }
}

TreeOfElements& TreeOfElements::operator=(const TreeOfElements& tree_to_assign){
     for(int i=top_elements.size()-1;i>=0;i--){
        delete top_elements[i];
        top_elements.pop_back();
     }
     for(int i=0;i<tree_to_assign.top_elements.size();i++){
        Element* tmp=new Element;
        tmp=tree_to_assign.top_elements[i];
        top_elements.push_back(tmp);
     }
     return *this;
}
TreeOfElements::~TreeOfElements(){
     for(int i=top_elements.size()-1;i>=0;i--){
        delete top_elements[i];
        top_elements.pop_back();
     }
}
