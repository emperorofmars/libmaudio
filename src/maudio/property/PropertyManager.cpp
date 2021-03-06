/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/property/PropertyManager.hpp"
#include <cstddef>

namespace maudio{

PropertyManager::PropertyManager(){
}

PropertyManager::~PropertyManager(){
}

void PropertyManager::add(IProperty *prop){
	if(!prop) return;
	if(PropertyExists(prop->getName())) return;
	mProperties.push_back(prop);
	notifyObservers(ON_CHANGE, "add");
	return;
}

void PropertyManager::add(IKeyableProperty *prop){
	if(!prop) return;
	if(KeyablePropertyExists(prop->getName())) return;
	mKeyableProperties.push_back(prop);
	notifyObservers(ON_CHANGE, "add");
	return;
}

bool PropertyManager::PropertyExists(const char *name){
	for(unsigned int i = 0; i < mProperties.size(); i++){
		if(std::string(mProperties[i]->getName()) == std::string(name)) return true;
	}
	return false;
}

bool PropertyManager::KeyablePropertyExists(const char *name){
	for(unsigned int i = 0; i < mKeyableProperties.size(); i++){
		if(std::string(mKeyableProperties[i]->getName()) == std::string(name)) return true;
	}
	return false;
}

IProperty *PropertyManager::getProperty(unsigned int i){
	if(i >= mProperties.size()) return NULL;
	return mProperties[i];
}

IProperty *PropertyManager::getProperty(const char *name){
	for(unsigned int i = 0; i < mProperties.size(); i++){
		if(std::string(mProperties[i]->getName()) == std::string(name)) return mProperties[i];
	}
	return NULL;
}

IKeyableProperty *PropertyManager::getKeyableProperty(unsigned int i){
	if(i >= mKeyableProperties.size()) return NULL;
	return mKeyableProperties[i];
}

IKeyableProperty *PropertyManager::getKeyableProperty(const char *name){
	for(unsigned int i = 0; i < mKeyableProperties.size(); i++){
		if(std::string(mKeyableProperties[i]->getName()) == std::string(name)) return mKeyableProperties[i];
	}
	return NULL;
}

void PropertyManager::removeProperty(unsigned int i){
	if(i >= mProperties.size()) return;
	mProperties.erase(mProperties.begin() + i);
	notifyObservers(ON_CHANGE, "remove");
	return;
}

void PropertyManager::removeProperty(const char *name){
	for(unsigned int i = 0; i < mProperties.size(); i++){
		if(std::string(mProperties[i]->getName()) == std::string(name)) mProperties.erase(mProperties.begin() + i);
	}
	notifyObservers(ON_CHANGE, "remove");
	return;
}

void PropertyManager::removeKeyableProperty(unsigned int i){
	if(i >= mKeyableProperties.size()) return;
	mKeyableProperties.erase(mKeyableProperties.begin() + i);
	notifyObservers(ON_CHANGE, "remove");
	return;
}

void PropertyManager::removeKeyableProperty(const char *name){
	for(unsigned int i = 0; i < mKeyableProperties.size(); i++){
		if(std::string(mKeyableProperties[i]->getName()) == std::string(name)) mKeyableProperties.erase(mKeyableProperties.begin() + i);
	}
	notifyObservers(ON_CHANGE, "remove");
	return;
}

unsigned int PropertyManager::getNumProperties() const{
	return mProperties.size();
}

unsigned int PropertyManager::getNumKeyableProperties() const{
	return mKeyableProperties.size();
}

} // maudio



