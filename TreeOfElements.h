#ifndef TREEOFELEMENTS_H
#define TREEOFELEMENTS_H
#include <vector>
#include <Element.h>

class TreeOfElements
{
    public:
        TreeOfElements(){};
        TreeOfElements(const TreeOfElements& tree_to_copy);
        TreeOfElements& operator=(const TreeOfElements& tree_to_assign);
        Element* AddLeaf(Element* parent_element,
                               Element* child_to_add);
        vector<Element*> GetTop()const {return top_elements;}
        void SetTop(Element* element_to_add){
            if(element_to_add!=nullptr){
                top_elements.push_back(element_to_add);
            }
        }
        ~TreeOfElements();
    protected:

    private:
        vector<Element*> top_elements;
};

#endif // TREEOFELEMENTS_H
