/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/property/Property.hpp"

namespace maudio{

Property::Property(const std::string &name){
    mName = name;
}

Property::~Property(){
}

std::string Property::getName() const{
    return mName;
}

} // maudio



