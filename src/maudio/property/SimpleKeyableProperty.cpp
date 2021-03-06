/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/property/SimpleKeyableProperty.hpp"

namespace maudio{

//bool
template<>
bool SimpleKeyableProperty<bool>::interpolate(long double pos) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	bool best = mValues.begin()->second;
	for(auto iter = mValues.begin(); iter != mValues.end(); iter++){
		if(iter->first <= pos){
			best = iter->second;
		}
		else return best;
	}
	return best;
}

template<>
const char *SimpleKeyableProperty<bool>::getString(long double pos) const{
	if(interpolate(pos)) return "true";
	else return "false";
}

template<>
const char *SimpleKeyableProperty<bool>::getKeyString(unsigned int keynum) const{
	if(interpolate(keynum)) return "true";
	else return "false";
}

//string
template<>
std::string SimpleKeyableProperty<std::string>::interpolate(long double pos) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	std::string best = mValues.begin()->second;
	for(auto iter = mValues.begin(); iter != mValues.end(); iter++){
		if(iter->first <= pos){
			best = iter->second;
		}
		else return best;
	}
	return best;
}

template<>
const char *SimpleKeyableProperty<std::string>::getString(long double pos) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return to_chararray(interpolate(pos));
}

template<>
std::string SimpleKeyableProperty<std::string>::get(long double pos) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return interpolate(pos);
}

template<>
const char *SimpleKeyableProperty<std::string>::getKeyString(unsigned int keynum) const{
	return to_chararray(getElement(keynum));
}

template<>
std::string SimpleKeyableProperty<std::string>::getKey(unsigned int keynum) const{
	return getElement(keynum);
}

template<>
void SimpleKeyableProperty<std::string>::addKey(const std::string &value, long double pos){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	mValues[pos] = value;
	notifyObservers(ON_CHANGE);
	return;
}

template<>
void SimpleKeyableProperty<std::string>::addKey(std::string value, long double pos){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	mValues[pos] = value;
	notifyObservers(ON_CHANGE);
	return;
}

template<>
void SimpleKeyableProperty<std::string>::setKey(const std::string &value, unsigned int keynum){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(keynum >= mValues.size()) return;

	auto iter = mValues.begin();
	while(iter != mValues.end() && keynum > 0){
		iter++;
		keynum--;
	}
	iter->second = value;
	notifyObservers(ON_CHANGE);
	return;
}

template<>
void SimpleKeyableProperty<std::string>::setKey(std::string value, unsigned int keynum){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(keynum >= mValues.size()) return;

	auto iter = mValues.begin();
	while(iter != mValues.end() && keynum > 0){
		iter++;
		keynum--;
	}
	iter->second = value;
	notifyObservers(ON_CHANGE);
	return;
}

template<>
void SimpleKeyableProperty<std::string>::setBounds(std::string bottom, std::string upper){
	return;
}

template<>
std::vector<std::string> SimpleKeyableProperty<std::string>::getBoundsString() const{
	return std::vector<std::string>(2);
}

template<>
std::vector<std::string> SimpleKeyableProperty<std::string>::getBounds() const{
	return std::vector<std::string>(2);
}

} // maudio



