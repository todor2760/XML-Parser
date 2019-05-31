#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <string>
#include <iostream>
#include <cstring>
using std::string;
class Attribute
{
    public:
        Attribute(){};
        Attribute(string key,string value);
        string GetKey()const{return key;}
        string GetValue()const{return value;}
        void SetValue(string value){
            if(!value.empty()){
                this->value=value;
            }
        }
        void SetKey(string key){
            if(!key.empty()){
                this->key=key;
            }
        }
    private:
        std::string key;
        std::string value;
};

#endif // ATTRIBUTE_H
