/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/property/SimpleProperty.hpp"
#include <exception>
#include <algorithm>
#include <limits>

namespace maudio{

//bool
template<>
SimpleProperty<bool>::SimpleProperty(const std::string &name, bool value)
	:Property(name)
{
	set(value);
	mBottomBound = std::numeric_limits<bool>::min();
	mUpperBound = std::numeric_limits<bool>::max();
}

template<>
std::string SimpleProperty<bool>::getString() const{
	if(mValue == true) return "true";
	return "false";
}

template<>
void SimpleProperty<bool>::set(const std::string &value){
	std::string tmp = value;
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if(tmp == "true" || tmp == "1") set(true);
	else set(true);
	return;
}

//int
template<>
SimpleProperty<int>::SimpleProperty(const std::string &name, int value)
	:Property(name)
{
	set(value);
	mBottomBound = std::numeric_limits<int>::min();
	mUpperBound = std::numeric_limits<int>::max();
}

template<>
std::string SimpleProperty<int>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<int>::set(const std::string &value){
	try{set(std::stoi(value));}
	catch(std::exception &e){
	}
	return;
}

//unsigned int
template<>
SimpleProperty<unsigned int>::SimpleProperty(const std::string &name, unsigned int value)
	:Property(name)
{
	set(value);
	mBottomBound = std::numeric_limits<unsigned int>::min();
	mUpperBound = std::numeric_limits<unsigned int>::max();
}

template<>
std::string SimpleProperty<unsigned int>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<unsigned int>::set(const std::string &value){
	try{set(std::stoul(value));}
	catch(std::exception &e){
	}
	return;
}

//long
template<>
SimpleProperty<long>::SimpleProperty(const std::string &name, long value)
	:Property(name)
{
	set(value);
	mBottomBound = std::numeric_limits<long>::min();
	mUpperBound = std::numeric_limits<long>::max();
}

template<>
std::string SimpleProperty<long>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<long>::set(const std::string &value){
	try{set(std::stol(value));}
	catch(std::exception &e){
	}
	return;
}

//unsigned long
template<>
SimpleProperty<unsigned long>::SimpleProperty(const std::string &name, unsigned long value)
	:Property(name)
{
	set(value);
	mBottomBound = std::numeric_limits<unsigned long>::min();
	mUpperBound = std::numeric_limits<unsigned long>::max();
}

template<>
std::string SimpleProperty<unsigned long>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<unsigned long>::set(const std::string &value){
	try{set(std::stoull(value));}
	catch(std::exception &e){
	}
	return;
}

//float
template<>
SimpleProperty<float>::SimpleProperty(const std::string &name, float value)
	:Property(name)
{
	set(value);
	mBottomBound = std::numeric_limits<float>::min();
	mUpperBound = std::numeric_limits<float>::max();
}

template<>
std::string SimpleProperty<float>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<float>::set(const std::string &value){
	try{set(std::stof(value));}
	catch(std::exception &e){
	}
	return;
}

//double
template<>
SimpleProperty<double>::SimpleProperty(const std::string &name, double value)
	:Property(name)
{
	set(value);
	mBottomBound = std::numeric_limits<double>::min();
	mUpperBound = std::numeric_limits<double>::max();
}

template<>
std::string SimpleProperty<double>::getString() const{
	return std::to_string(mValue);
}

template<>
void SimpleProperty<double>::set(const std::string &value){
	try{set(std::stod(value));}
	catch(std::exception &e){
	}
	return;
}

//string
template<>
void SimpleProperty<std::string>::set(std::string value){
	mValue = value;
	return;
}

template<>
void SimpleProperty<std::string>::setBounds(std::string bottom, std::string upper){
	return;
}

template<>
std::vector<std::string> SimpleProperty<std::string>::getBoundsString() const{
	return std::vector<std::string>();
}

template<>
std::vector<std::string> SimpleProperty<std::string>::getBounds() const{
	return std::vector<std::string>{"0", "0"};
}

} // maudio



