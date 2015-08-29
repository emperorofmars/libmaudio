/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_MULTISTORE
#define MAUDIO_MULTISTORE

#include "core/store/IMultiStore.hpp"
#include "core/util/Util.hpp"
#include "core/util/AudioException.hpp"
#include <map>
#include <string>

namespace maudio{

class MultiStore : public IMultiStore{
public:
	MultiStore();
	virtual ~MultiStore();

	virtual const char *get(const char *key, unsigned int numElm = 0) const;
	template<typename T>
	T get(const char *key, unsigned int numElm = 0) const;
	virtual const char *get(unsigned int numKey, unsigned int numElm = 0) const;
	template<typename T>
	T get(unsigned int numKey, unsigned int numElm = 0) const;
	virtual unsigned int getSize() const;
	virtual unsigned int getSize(const char *key) const;
	virtual unsigned int getSize(unsigned int numKey) const;
	virtual void add(const char *key, const char *value);
	template<typename T>
	void add(const char *key, T value);

private:
	bool checkKey(const std::string &key) const;

	std::multimap<std::string, std::string> mData;
};

template<typename T>
T MultiStore::get(const char *key, unsigned int numElm) const{
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
	return string_to<T>(iter->second);
}

template<typename T>
T MultiStore::get(unsigned int numKey, unsigned int numElm) const{
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
	return string_to<T>(iter->second);
}

template<typename T>
void MultiStore::add(const char *key, T value){
	std::string tmpKey(key);
	if(!checkKey(tmpKey)) return;
	mData.insert(std::make_pair(tmpKey, std::to_string(value)));
	return;
}

} // maudio

#endif // MAUDIO_MULTISTORE




