/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/store/MultiLevelStore.hpp"

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

const char *MultiLevelStore::get(unsigned int numKey) const{
	if(numKey >= mData.size()) throw MaudioException("numKey out of range");
	auto iter = mData.begin();
	while(iter != mData.end() && numKey != 0){
		iter++;
		numKey--;
	}
	return iter->second.c_str();
}

const char *MultiLevelStore::getKey(unsigned int numKey) const{
	if(numKey >= mData.size()) throw MaudioException("numKey out of range");
	auto iter = mData.begin();
	while(iter != mData.end() && numKey != 0){
		iter++;
		numKey--;
	}
	return iter->first.c_str();
}

IMultiLevelStore *MultiLevelStore::getLevel(const char *key, unsigned int numElm) const{
	if(!key) throw MaudioException("key doesn't exist");
	std::string tmpKey(key);
	if(mLevels.find(tmpKey) == mLevels.end()) throw MaudioException("key doesn't exist");
	auto iter = mLevels.lower_bound(tmpKey);
	auto iterUp = mLevels.upper_bound(tmpKey);
	while(iter != iterUp && numElm != 0){
		iter++;
		numElm--;
	}
	if(numElm != 0) throw MaudioException("numElm out of range");
	return iter->second.get();
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

const char *MultiLevelStore::getLevelKey(unsigned int numKey) const{
	if(numKey >= mLevels.size()) throw MaudioException("numKey out of range");
	auto iter = mLevels.begin();
	while(iter != mLevels.end() && numKey != 0){
		iter++;
		numKey--;
	}
	return iter->first.c_str();
}

unsigned int MultiLevelStore::getSize() const{
	return mData.size();
}

unsigned int MultiLevelStore::getSize(const char *key) const{
	return mData.count(std::string(key));
}

unsigned int MultiLevelStore::getNumLevels() const{
	return mLevels.size();
}

unsigned int MultiLevelStore::getNumLevels(const char *key) const{
	return mLevels.count(std::string(key));
}

void MultiLevelStore::add(const char *key, const char *value){
	std::string tmpKey(key);
	if(!checkKey(tmpKey)) return;
	mData.insert(std::make_pair(tmpKey, std::string(value)));
	return;
}

IMultiLevelStore *MultiLevelStore::addLevel(const char *key){
	std::string tmpKey(key);
	MultiLevelStore *ret = new MultiLevelStore();
	mLevels.insert(std::make_pair(tmpKey, std::unique_ptr<MultiLevelStore>(ret)));
	return ret;
}

bool MultiLevelStore::checkKey(const std::string &key) const{
	if(key.size() == 0) return false;
	if(key[0] == '!') return false;
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] == ' ' || key[i] == '\t') return false;
	}
	return true;
}

} // maudio



