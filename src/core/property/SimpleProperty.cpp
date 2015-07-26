/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/property/SimpleProperty.hpp"
#include <exception>
#include <algorithm>

namespace maudio{

//bool
template<>
std::string SimpleProperty<bool>::getString() const{
	if(mValue == true) return "true";
	return "false";
}

template<>
void SimpleProperty<bool>::set(const std::string &value){
	std::string tmp = value;
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if(tmp == "true" || tmp == "1") mValue = true;
	else mValue = false;
	return;
}

template<>
std::string SimpleProperty<bool>::getBounds() const{
	return "0, 1";
}

//int
template<>
std::string SimpleProperty<int>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<int>::set(const std::string &value){
	try{mValue = std::stoi(value);}
	catch(std::exception &e){
	}
	return;
}

//unsigned int
template<>
std::string SimpleProperty<unsigned int>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<unsigned int>::set(const std::string &value){
	try{mValue = std::stoul(value);}
	catch(std::exception &e){
	}
	return;
}

//long
template<>
std::string SimpleProperty<long>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<long>::set(const std::string &value){
	try{mValue = std::stol(value);}
	catch(std::exception &e){
	}
	return;
}

//unsigned long
template<>
std::string SimpleProperty<unsigned long>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<unsigned long>::set(const std::string &value){
	try{mValue = std::stoull(value);}
	catch(std::exception &e){
	}
	return;
}

//float
template<>
std::string SimpleProperty<float>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<float>::set(const std::string &value){
	try{mValue = std::stof(value);}
	catch(std::exception &e){
	}
	return;
}

//double
template<>
std::string SimpleProperty<double>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<double>::set(const std::string &value){
	try{mValue = std::stod(value);}
	catch(std::exception &e){
	}
	return;
}

} // maudio



