#include "Attribute.h"

Attribute::Attribute(string key,string value)
{
    if(!key.empty()){
        this->key=key;
    }
    if(!value.empty()){
        this->value=value;
    }
}


