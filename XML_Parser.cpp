#include "XML_Parser.h"

void XML_Parser::CreateTree(Element* parent_element,int depth){
    string line;
    if(XML_Parser::IsOpened()){
        while(std::getline(myXmlFile,line)){
            string element_name;
            string element_id;
            string element_other_information;
            vector<Attribute> element_attributes;

            if(depth==0){
                int line_index=0;
                while(line_index<line.length()&&line[line_index]!='<'){
                    line_index++;
                }
                line_index++;
                if(line[line_index]!='/'){
                        while(line[line_index]!=' '&&line[line_index]!='>'){
                            element_name.push_back(line[line_index]);
                            line_index++;
                        }
                        line_index++;
                        while(line_index<line.length()&&line[line_index]!='>'){
                            string key,value;
                            while(line_index<line.length()&&line[line_index]!='='){
                                key.push_back(line[line_index]);
                                line_index++;
                            }
                            line_index+=2;
                            while(line_index<line.length()&&line[line_index]!='\"'){
                                value.push_back(line[line_index]);
                                line_index++;
                            }
                            line_index++;
                            if(line_index<line.length()&&line[line_index]==' '){
                                line_index++;
                            }
                            if(strcmp(key.c_str(),"id")!=0){
                                Attribute tmp_attribute(key,value);
                                element_attributes.push_back(tmp_attribute);
                            }
                            else{element_id=value;}
                        }
                        if(line_index<line.length()&&line[line_index]=='>'){
                            line_index++;
                        }
                        while(line_index<line.length()&&line[line_index]!='<'){
                            element_other_information.push_back(line[line_index]);
                            line_index++;
                        }
                        line_index++;
                        Element* tmp_element=new Element(element_name,element_id,element_other_information,
                                            element_attributes);
                        tree_of_elements.SetTop(tmp_element);
                        if(line_index>line.length()||line[line_index]!='/'){
                            XML_Parser::CreateTree(tree_of_elements.GetTop().back(),depth+1);
                        }
                }
           }
           else if(depth>0){
                int line_index=0;
                while(line_index<line.length()&&line[line_index]!='<'){
                    line_index++;
                }
                line_index++;
                if(line[line_index]!='/'){
                        while(line[line_index]!=' '&&line[line_index]!='>'){
                            element_name.push_back(line[line_index]);
                            line_index++;
                        }
                        line_index++;
                        while(line_index<line.length()&&line[line_index]!='>'){
                            string key,value;
                            while(line_index<line.length()&&line[line_index]!='='){
                                key.push_back(line[line_index]);
                                line_index++;
                            }
                            line_index+=2;
                            while(line_index<line.length()&&line[line_index]!='\"'){
                                value.push_back(line[line_index]);
                                line_index++;
                            }
                            line_index++;
                            if(line_index<line.length()&&line[line_index]==' '){
                                line_index++;
                            }
                            if(strcmp(key.c_str(),"id")!=0){
                                Attribute tmp_attribute(key,value);
                                element_attributes.push_back(tmp_attribute);
                            }
                            else{element_id=value;}
                        }
                        if(line_index<line.length()&&line[line_index]=='>'){
                            line_index++;
                        }
                        while(line_index<line.length()&&line[line_index]!='<'){
                            element_other_information.push_back(line[line_index]);
                            line_index++;
                        }
                        while(line_index<line.length()&&line[line_index]!='<'){
                            line_index++;
                        }
                        line_index++;
                        Element* tmp_element=new Element(element_name,element_id,element_other_information,
                                            element_attributes);
                        tree_of_elements.AddLeaf(parent_element,tmp_element);
                        if(line_index>line.length()||line[line_index]!='/'){
                            XML_Parser::CreateTree(parent_element->GetChildrenElements().back(),depth+1);
                        }
               }
               else{return;}
           }
        }
    }
}
bool XML_Parser::SeekingInTheTree(Element* parent_element,int depth,Element* current_element,string id,bool found_match){
    if(depth==0){
        for(int top_elements_index=0;
        top_elements_index<tree_of_elements.GetTop().size();
        top_elements_index++){
            if(!tree_of_elements.GetTop()[top_elements_index]->GetId().empty()){
               if(strcmp(tree_of_elements.GetTop()[top_elements_index]->GetId().c_str(),
                                  id.c_str())==0&&
                  tree_of_elements.GetTop()[top_elements_index]!=current_element){
                      return found_match=true;
               }
            }
            found_match=XML_Parser::SeekingInTheTree(tree_of_elements.GetTop()[top_elements_index],depth+1,current_element,id,found_match);
        }
        return found_match;
    }
    else if(depth>0){
        for(int children_elements_index=0;
        children_elements_index<parent_element->GetChildrenElements().size();
        children_elements_index++){
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetId().empty()){
                  if(strcmp(parent_element->GetChildrenElements()[children_elements_index]->GetId().c_str(),
                                  id.c_str())==0&&
                     parent_element->GetChildrenElements()[children_elements_index]!=current_element){
                        return found_match=true;
               }
            }
            found_match=XML_Parser::SeekingInTheTree(parent_element->GetChildrenElements()[children_elements_index],depth+1,current_element,id,found_match);
        }
        return found_match;
    }
}

void XML_Parser::CreateUniqueIds(Element* parent_element,int depth){
    if(depth==0){
        for(int top_elements_index=0;
        top_elements_index<tree_of_elements.GetTop().size();
        top_elements_index++){
            bool found_match;
            if(!tree_of_elements.GetTop()[top_elements_index]->GetId().empty()){
                 found_match=XML_Parser::SeekingInTheTree(nullptr,0,tree_of_elements.GetTop()[top_elements_index],tree_of_elements.GetTop()[top_elements_index]->GetId(),false);
                 int unique_id=0;
                 while(found_match){
                    tree_of_elements.GetTop()[top_elements_index]->SetId(std::to_string(unique_id));
                    found_match=XML_Parser::SeekingInTheTree(nullptr,0,tree_of_elements.GetTop()[top_elements_index],tree_of_elements.GetTop()[top_elements_index]->GetId(),false);
                    unique_id++;
                 }
            }
            else{
                 found_match=true;
                 int unique_id=0;
                 while(found_match){
                    tree_of_elements.GetTop()[top_elements_index]->SetId(std::to_string(unique_id));
                    found_match=XML_Parser::SeekingInTheTree(nullptr,0,tree_of_elements.GetTop()[top_elements_index],tree_of_elements.GetTop()[top_elements_index]->GetId(),false);
                    unique_id++;
                 }
            }
            XML_Parser::CreateUniqueIds(tree_of_elements.GetTop()[top_elements_index],depth+1);
        }
    }
    else if(depth>0){
        for(int children_elements_index=0;
        children_elements_index<parent_element->GetChildrenElements().size();
        children_elements_index++){
            bool found_match;
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetId().empty()){
                    found_match=XML_Parser::SeekingInTheTree(nullptr,0,parent_element->GetChildrenElements()[children_elements_index],parent_element->GetChildrenElements()[children_elements_index]->GetId(),false);
                    int unique_id=0;
                    while(found_match){
                       parent_element->GetChildrenElements()[children_elements_index]->SetId(std::to_string(unique_id));
                       found_match=XML_Parser::SeekingInTheTree(nullptr,0,parent_element->GetChildrenElements()[children_elements_index],parent_element->GetChildrenElements()[children_elements_index]->GetId(),false);
                       unique_id++;
                    }
            }
            else{
                    found_match=true;
                    int unique_id=0;
                    while(found_match){
                       parent_element->GetChildrenElements()[children_elements_index]->SetId(std::to_string(unique_id));
                       found_match=XML_Parser::SeekingInTheTree(nullptr,0,parent_element->GetChildrenElements()[children_elements_index],parent_element->GetChildrenElements()[children_elements_index]->GetId(),false);
                       unique_id++;
                    }
            }
            XML_Parser::CreateUniqueIds(parent_element->GetChildrenElements()[children_elements_index],depth+1);
        }
    }
}


Element XML_Parser::SeekingInTheTree(Element* parent_element,int depth,string id,Element found_match,bool is_changing){
    if(depth==0){
        for(int top_elements_index=0;
        top_elements_index<tree_of_elements.GetTop().size();
        top_elements_index++){
            if(!tree_of_elements.GetTop()[top_elements_index]->GetId().empty()){
               if(strcmp(tree_of_elements.GetTop()[top_elements_index]->GetId().c_str(),
                                  id.c_str())==0){
                      found_match=*tree_of_elements.GetTop()[top_elements_index];
                      return found_match;
               }
            }
            found_match=XML_Parser::SeekingInTheTree(tree_of_elements.GetTop()[top_elements_index],depth+1,id,found_match,is_changing);
        }
        return found_match;
    }
    else if(depth>0){
        for(int children_elements_index=0;
        children_elements_index<parent_element->GetChildrenElements().size();
        children_elements_index++){
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetId().empty()){
                  if(strcmp(parent_element->GetChildrenElements()[children_elements_index]->GetId().c_str(),
                                  id.c_str())==0){
                        found_match=*parent_element->GetChildrenElements()[children_elements_index];
                        return found_match;
               }
            }
            found_match=XML_Parser::SeekingInTheTree(parent_element->GetChildrenElements()[children_elements_index],depth+1,id,found_match,is_changing);
        }
        return found_match;
    }
}

void XML_Parser::CloseFile(){
    if(XML_Parser::IsOpened()){
        myXmlFile.close();
        cout<<"the file was closed"<<endl;
    }
    else{cout<<"there isn't an opened file"<<endl;}
}

void XML_Parser::OpenFile(){
    TreeOfElements empty_tree;
    tree_of_elements=empty_tree;
    tree_of_elements=tree_of_elements;
    cout<<"Type file path:"<<endl;
    cin>>path;
    myXmlFile.open(path.c_str(),std::ios::in | std::ios::out);
    this->CreateTree(nullptr,0);
    this->CreateUniqueIds(nullptr,0);
}

void XML_Parser::SaveRecursiveFunc(Element* parent_element,int depth){
    if(depth==0){
        for(int top_elements_index=0;
        top_elements_index<tree_of_elements.GetTop().size();
        top_elements_index++){
            if(!tree_of_elements.GetTop()[top_elements_index]->GetName().empty()){
                  myXmlFile<<"<"<<tree_of_elements.GetTop()[top_elements_index]->GetName();
            }
            if(!tree_of_elements.GetTop()[top_elements_index]->GetId().empty()){
                  myXmlFile<<" "<<"id=\""<<tree_of_elements.GetTop()[top_elements_index]->GetId()<<"\"";
            }
            if(tree_of_elements.GetTop()[top_elements_index]->GetAttributes().size()>0){
                  for(int attributes_number=0;
                  attributes_number<tree_of_elements.GetTop()[top_elements_index]->GetAttributes().size();
                  attributes_number++){
                       myXmlFile<<" "<<tree_of_elements.GetTop()[top_elements_index]->GetAttributes()[attributes_number].GetKey();
                       myXmlFile<<"=\""<<tree_of_elements.GetTop()[top_elements_index]->GetAttributes()[attributes_number].GetValue()<<"\"";
                  }
            }
            myXmlFile<<">";
            if(tree_of_elements.GetTop()[top_elements_index]->GetChildrenElements().size()>0){
                myXmlFile<<endl;
            }
            if(!tree_of_elements.GetTop()[top_elements_index]->GetText().empty()){
                  myXmlFile<<tree_of_elements.GetTop()[top_elements_index]->GetText();
            }
            XML_Parser::SaveRecursiveFunc(tree_of_elements.GetTop()[top_elements_index],depth+1);
            myXmlFile<<"</"<<tree_of_elements.GetTop()[top_elements_index]->GetName()<<">"<<endl;
        }
    }
    else if(depth>0){
        for(int children_elements_index=0;
        children_elements_index<parent_element->GetChildrenElements().size();
        children_elements_index++){
            for(int interval=0;interval<depth;interval++){
                  myXmlFile<<"  ";
            }
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetName().empty()){
                  myXmlFile<<"<"<<parent_element->GetChildrenElements()[children_elements_index]->GetName();
            }
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetId().empty()){
                  myXmlFile<<" "<<"id=\""<<parent_element->GetChildrenElements()[children_elements_index]->GetId()<<"\"";
            }
            if(parent_element->GetChildrenElements()[children_elements_index]->GetAttributes().size()>0){
                  for(int attributes_number=0;
                  attributes_number<parent_element->GetChildrenElements()[children_elements_index]->GetAttributes().size();
                  attributes_number++){
                       myXmlFile<<" "<<parent_element->GetChildrenElements()[children_elements_index]->GetAttributes()[attributes_number].GetKey();
                       myXmlFile<<"=\""<<parent_element->GetChildrenElements()[children_elements_index]->GetAttributes()[attributes_number].GetValue()<<"\"";
                  }

            }
            myXmlFile<<">";
            if(parent_element->GetChildrenElements()[children_elements_index]->GetChildrenElements().size()>0){
                myXmlFile<<endl;
            }
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetText().empty()){
                  myXmlFile<<parent_element->GetChildrenElements()[children_elements_index]->GetText();
            }
            XML_Parser::SaveRecursiveFunc(parent_element->GetChildrenElements()[children_elements_index],depth+1);
            if(parent_element->GetChildrenElements()[children_elements_index]->GetChildrenElements().size()>0){
                for(int interval=0;interval<depth;interval++){
                  myXmlFile<<"  ";
                }
            }
            myXmlFile<<"</"<<parent_element->GetChildrenElements()[children_elements_index]->GetName()<<">"<<endl;
        }
    }
}

void XML_Parser::SaveFile(bool save_as){
    XML_Parser::CloseFile();
    myXmlFile.open(path.c_str(),std::ios::out | std::ios::trunc);
    if(myXmlFile.is_open()){
        XML_Parser::SaveRecursiveFunc(nullptr,0);
    }
    XML_Parser::CloseFile();
}

void XML_Parser::XML_Print(Element* parent_element,int depth){
    if(depth==0){
        for(int top_elements_index=0;
        top_elements_index<tree_of_elements.GetTop().size();
        top_elements_index++){
            if(!tree_of_elements.GetTop()[top_elements_index]->GetName().empty()){
                  cout<<tree_of_elements.GetTop()[top_elements_index]->GetName();
            }
            if(!tree_of_elements.GetTop()[top_elements_index]->GetId().empty()){
                  cout<<" "<<"id=\""<<tree_of_elements.GetTop()[top_elements_index]->GetId()<<"\"";
            }
            if(tree_of_elements.GetTop()[top_elements_index]->GetAttributes().size()>0){
                  for(int attributes_number=0;
                  attributes_number<tree_of_elements.GetTop()[top_elements_index]->GetAttributes().size();
                  attributes_number++){
                       cout<<" "<<tree_of_elements.GetTop()[top_elements_index]->GetAttributes()[attributes_number].GetKey();
                       cout<<"=\""<<tree_of_elements.GetTop()[top_elements_index]->GetAttributes()[attributes_number].GetValue()<<"\"";
                  }

            }
            if(!tree_of_elements.GetTop()[top_elements_index]->GetText().empty()){
                  cout<<" : "<<tree_of_elements.GetTop()[top_elements_index]->GetText();
            }
            cout<<endl;
            XML_Parser::XML_Print(tree_of_elements.GetTop()[top_elements_index],depth+1);
        }
    }
    else if(depth>0){
        for(int children_elements_index=0;
        children_elements_index<parent_element->GetChildrenElements().size();
        children_elements_index++){
            for(int interval=0;interval<depth;interval++){
                cout<<"  ";
            }
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetName().empty()){
                  cout<<parent_element->GetChildrenElements()[children_elements_index]->GetName();
            }
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetId().empty()){
                  cout<<" "<<"id=\""<<parent_element->GetChildrenElements()[children_elements_index]->GetId()<<"\"";
            }
            if(parent_element->GetChildrenElements()[children_elements_index]->GetAttributes().size()>0){
                  for(int attributes_number=0;
                  attributes_number<parent_element->GetChildrenElements()[children_elements_index]->GetAttributes().size();
                  attributes_number++){
                       cout<<" "<<parent_element->GetChildrenElements()[children_elements_index]->GetAttributes()[attributes_number].GetKey();
                       cout<<"=\""<<parent_element->GetChildrenElements()[children_elements_index]->GetAttributes()[attributes_number].GetValue()<<"\"";
                  }

            }
            if(!parent_element->GetChildrenElements()[children_elements_index]->GetText().empty()){
                  cout<<" : "<<parent_element->GetChildrenElements()[children_elements_index]->GetText();
            }
            cout<<endl;
            XML_Parser::XML_Print(parent_element->GetChildrenElements()[children_elements_index],depth+1);
        }
    }
}

void XML_Parser::SelectAttribute(){
     string id,key;
     cout<<"Type the id of the element"<<endl;
     cin>>id;
     cout<<"Type the key of the element"<<endl;
     cin>>key;
     Element select_attribute;
     if(!id.empty()){
        select_attribute=XML_Parser::SeekingInTheTree(nullptr,0,id,select_attribute,false);
        if(select_attribute.GetId().empty()){
            cout<<"there isn't an element with this id"<<endl;
            return;
        }
        if(!key.empty()){
            int i=0;
            while(i<select_attribute.GetAttributes().size()&&
                  select_attribute.GetAttributes()[i].GetKey()!=key){
                i++;
            }
            if(i<select_attribute.GetAttributes().size()){
                cout<<key<<"="<<select_attribute.GetAttributes()[i].GetValue()<<endl;
            }
            else{
                cout<<"there isn't an element with this attribute"<<endl;
            }
        }
     }
}

void XML_Parser::ChangeAttributeValue(){
     string id,key,value;
     cout<<"Type the id of the element"<<endl;
     cin>>id;
     cout<<"Type the key of the element"<<endl;
     cin>>key;
     if(!id.empty()){

     }
}

void XML_Parser::ChildrenAttributes(){
     string id;
     cout<<"Type the id of the element"<<endl;
     cin>>id;
     Element select_parent;
     if(!id.empty()){
        select_parent=XML_Parser::SeekingInTheTree(nullptr,0,id,select_parent,false);
        if(select_parent.GetId().empty()){
            cout<<"there isn't an element with this id"<<endl;
            return;
        }
        else{
            for(int i=0;i<select_parent.GetChildrenElements().size();i++){
                for(int j=0;j<select_parent.GetChildrenElements()[i]->GetAttributes().size();j++){
                    cout<<"Child number "<<i+1<<" ";
                    cout<<" "<<select_parent.GetChildrenElements()[i]->GetAttributes()[j].GetKey();
                    cout<<"=\""<<select_parent.GetChildrenElements()[i]->GetAttributes()[j].GetValue();
                    cout<<"\" "<<endl;
                }
            }
        }
     }
}

void XML_Parser::GetText(){
     string id;
     cout<<"Type the id of the element"<<endl;
     cin>>id;
     Element select_text;
     if(!id.empty()){
        select_text=XML_Parser::SeekingInTheTree(nullptr,0,id,select_text,false);
        if(select_text.GetId().empty()){
            cout<<"there isn't an element with this id"<<endl;
            return;
        }
        else if(!select_text.GetText().empty()){
            cout<<select_text.GetText()<<endl;
        }
        else{cout<<"the element doesn't have text"<<endl;}
    }
}

void XML_Parser::GetNChild(){
     string id;
     int N;
     cout<<"Type the id of the element"<<endl;
     cin>>id;
     cout<<"Type N"<<endl;
     cin>>N;
     Element select_N_child;
     if(!id.empty()){
        select_N_child=XML_Parser::SeekingInTheTree(nullptr,0,id,select_N_child,false);
        if(select_N_child.GetId().empty()){
            cout<<"there isn't an element with this id"<<endl;
            return;
        }
        else if(select_N_child.GetChildrenElements().size()>0){
            if(select_N_child.GetChildrenElements().size()>=N){
                cout<<"the "<<N<<" child is "<<select_N_child.GetChildrenElements()[N-1]->GetName()<<endl;
            }
            else{cout<<"the element doesn't have "<<N<<" child"<<endl;}
        }
        else{cout<<"the element doesn't have children"<<endl;}
    }
}

void XML_Parser::DeleteAttribute(){

}

void XML_Parser::AddNewInheritor(){

}
