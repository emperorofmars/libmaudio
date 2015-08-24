/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/store/KeyValueStore.hpp"

namespace maudio{

KeyValueStore::KeyValueStore(){
}

KeyValueStore::~KeyValueStore(){
}

const char *KeyValueStore::get(const char *key) const{
	return mData.at(key).c_str();
}

std::string KeyValueStore::get(const std::string &key) const{
	return mData.at(key);
}

template<>
std::string KeyValueStore::get(const std::string &key) const{
	try{
		return mData.at(key);
	}
	catch(std::exception &e){
		throw e;
	}
}

const char *KeyValueStore::get(unsigned int numKey) const{
	if(numKey >= mData.size()) throw MaudioException("numKey out of range");
	auto iter = mData.begin();
	while(iter != mData.end() && numKey > 0){
		iter++;
		numKey--;
	}
	return iter->second.c_str();
}

template<>
std::string KeyValueStore::get(unsigned int numKey) const{
	if(numKey >= mData.size()) throw MaudioException("numKey out of range");
	auto iter = mData.begin();
	while(iter != mData.end() && numKey > 0){
		iter++;
		numKey--;
	}
	return iter->second;
}

unsigned int KeyValueStore::getSize() const{
	return mData.size();
}

void KeyValueStore::set(const char *key, const char *value){
	if(!checkKey(key)) return;
	mData[key] = value;
	return;
}

void KeyValueStore::set(const std::string &key, const std::string &value){
	if(!checkKey(key)) return;
	mData[key] = value;
	return;
}

template<>
void KeyValueStore::set(const std::string &key, std::string value){
	if(!checkKey(key)) return;
	mData[key] = value;
	return;
}

bool KeyValueStore::checkKey(const std::string &key) const{
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] == ' ' || key[i] == '\t') return false;
	}
	return true;
}

} // maudio



