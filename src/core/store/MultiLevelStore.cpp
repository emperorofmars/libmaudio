/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/store/MultiLevelStore.hpp"

#include <iostream>

namespace maudio{

MultiLevelStore::MultiLevelStore(){
}

MultiLevelStore::~MultiLevelStore(){
}

const char *MultiLevelStore::get(const char *key, unsigned int numElm) const{
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

const char *MultiLevelStore::get(unsigned int numKey, unsigned int numElm) const{
	if(numKey >= mData.size()) throw MaudioException("numKey out of range");
	auto iter = mData.begin();
	while(iter != mData.end() && numKey != 0){
		iter++;
		numKey--;
	}
	auto iterUp = mData.upper_bound(iter->first);
	while(iter != iterUp && numElm != 0){
		iter++;
		numElm--;
	}
	if(numElm != 0) throw MaudioException("numElm out of range");
	return iter->second.c_str();
}

IMultiLevelStore *MultiLevelStore::getLevel(const char *key) const{
	return mLevels.at(key).get();
}

IMultiLevelStore *MultiLevelStore::getLevel(unsigned int numKey) const{
	if(numKey >= mLevels.size()) throw MaudioException("numKey out of range");
	auto iter = mLevels.begin();
	while(iter != mLevels.end() && numKey != 0){
		iter++;
		numKey--;
	}
	return iter->second.get();
}

unsigned int MultiLevelStore::getSize() const{
	return mData.size();
}

unsigned int MultiLevelStore::getSize(const char *key) const{
	return mData.count(std::string(key));
}

unsigned int MultiLevelStore::getSize(unsigned int numKey) const{
	if(numKey >= mData.size()) return 0;
	auto iter = mData.begin();
	while(iter != mData.end() && numKey != 0){
		iter++;
		numKey--;
	}
	return mData.count(iter->first);
}

unsigned int MultiLevelStore::getNumLevels() const{
	return mLevels.size();
}

void MultiLevelStore::add(const char *key, const char *value){
	std::string tmpKey(key);
	if(!checkKey(tmpKey)) return;
	mData.insert(std::make_pair(tmpKey, std::string(value)));
	return;
}

void MultiLevelStore::addLevel(const char *key){
	std::string tmpKey(key);
	mLevels[tmpKey] = std::unique_ptr<MultiLevelStore>(new MultiLevelStore());
	return;
}

bool MultiLevelStore::checkKey(const std::string &key) const{
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] == ' ' || key[i] == '\t') return false;
	}
	return true;
}

} // maudio



