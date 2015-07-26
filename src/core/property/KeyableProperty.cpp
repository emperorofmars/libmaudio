/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/property/KeyableProperty.hpp"

namespace maudio{

KeyableProperty::KeyableProperty(const std::string &name){
    mName = name;
}

KeyableProperty::~KeyableProperty(){
}

std::string KeyableProperty::getName() const{
    return mName;
}

} // maudio



