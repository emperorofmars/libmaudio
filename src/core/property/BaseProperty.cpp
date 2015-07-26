/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/property/BaseProperty.hpp"
#include <exception>
#include <algorithm>

namespace maudio{

//bool
template<>
std::string BaseProperty<bool>::getString() const{
	if(mValue == true) return "true";
	return "false";
}

template<>
void BaseProperty<bool>::set(const std::string &value){
	std::string tmp = value;
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if(tmp == "true" || tmp == "1") mValue = true;
	else mValue = false;
	return;
}

template<>
std::string BaseProperty<bool>::getBounds() const{
	return "0, 1";
}

//int
template<>
std::string BaseProperty<int>::getString() const{
	return std::to_string(mValue);
}

template<>
void BaseProperty<int>::set(const std::string &value){
	try{mValue = std::stoi(value);}
	catch(std::exception &e){
	}
	return;
}

//unsigned int
template<>
std::string BaseProperty<unsigned int>::getString() const{
	return std::to_string(mValue);
}

template<>
void BaseProperty<unsigned int>::set(const std::string &value){
	try{mValue = std::stoul(value);}
	catch(std::exception &e){
	}
	return;
}

//long
template<>
std::string BaseProperty<long>::getString() const{
	return std::to_string(mValue);
}

template<>
void BaseProperty<long>::set(const std::string &value){
	try{mValue = std::stol(value);}
	catch(std::exception &e){
	}
	return;
}

//unsigned long
template<>
std::string BaseProperty<unsigned long>::getString() const{
	return std::to_string(mValue);
}

template<>
void BaseProperty<unsigned long>::set(const std::string &value){
	try{mValue = std::stoull(value);}
	catch(std::exception &e){
	}
	return;
}

//float
template<>
std::string BaseProperty<float>::getString() const{
	return std::to_string(mValue);
}

template<>
void BaseProperty<float>::set(const std::string &value){
	try{mValue = std::stof(value);}
	catch(std::exception &e){
	}
	return;
}

//double
template<>
std::string BaseProperty<double>::getString() const{
	return std::to_string(mValue);
}

template<>
void BaseProperty<double>::set(const std::string &value){
	try{mValue = std::stod(value);}
	catch(std::exception &e){
	}
	return;
}

} // maudio



