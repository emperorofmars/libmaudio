/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/property/SimpleProperty.hpp"
#include <exception>
#include <limits>

namespace maudio{

//bool
template<>
const char *SimpleProperty<bool>::getString() const{
	if(mValue) return "true";
	else return "false";
}

//string
template<>
void SimpleProperty<std::string>::set(std::string value){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	mValue = value;
	notifyObservers(ON_CHANGE);
	return;
}

template<>
void SimpleProperty<std::string>::setBounds(std::string bottom, std::string upper){
	return;
}

template<>
std::vector<std::string> SimpleProperty<std::string>::getBoundsString() const{
	return std::vector<std::string>(2);
}

template<>
std::vector<std::string> SimpleProperty<std::string>::getBounds() const{
	return std::vector<std::string>(2);
}

} // maudio



