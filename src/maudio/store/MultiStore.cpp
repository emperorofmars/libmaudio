/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/store/MultiStore.hpp"

namespace maudio{

MultiStore::MultiStore(){
}

MultiStore::~MultiStore(){
}

const char *MultiStore::get(const char *key, unsigned int numElm) const{
	if(!key) throw MaudioException("key doesn't exist");
	std::string tmpKey(key);
	if(mData.find(tmpKey) == mData.end()) throw MaudioException("key doesn't exist");
	auto iter = mData.lower_bound(tmpKey);
	auto iterUp = mData.upper_bound(tmpKey);
	while(iter != iterUp && numElm != 0){
		iter++;
		numElm--;
	}
	if(numElm != 0) throw MaudioException("numElm out of range");
	return iter->second.c_str();
}

const char *MultiStore::get(unsigned int numKey) const{
	if(numKey >= mData.size()) throw MaudioException("numKey out of range");
	auto iter = mData.begin();
	while(iter != mData.end() && numKey != 0){
		iter++;
		numKey--;
	}
	return iter->second.c_str();
}

const char *MultiStore::getKey(unsigned int numKey) const{
	if(numKey >= mData.size()) throw MaudioException("numKey out of range");
	auto iter = mData.begin();
	while(iter != mData.end() && numKey != 0){
		iter++;
		numKey--;
	}
	return iter->first.c_str();
}

unsigned int MultiStore::getSize() const{
	return mData.size();
}

unsigned int MultiStore::getSize(const char *key) const{
	return mData.count(std::string(key));
}

void MultiStore::add(const char *key, const char *value){
	std::string tmpKey(key);
	if(!checkKey(tmpKey)) return;
	mData.insert(std::make_pair(tmpKey, std::string(value)));
	return;
}

bool MultiStore::checkKey(const std::string &key) const{
	if(key.size() == 0) return false;
	if(key[0] == '!') return false;
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] == ' ' || key[i] == '\t') return false;
	}
	return true;
}

} // maudio



