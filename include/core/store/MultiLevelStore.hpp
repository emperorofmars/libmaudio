/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_MULTLEVELISTORE
#define MAUDIO_MULTLEVELISTORE

#include "core/store/IMultiLevelStore.hpp"
#include "core/util/Util.hpp"
#include "core/util/AudioException.hpp"
#include <map>
#include <string>
#include <memory>

namespace maudio{

class MultiLevelStore : public IMultiLevelStore{
public:
	MultiLevelStore();
	virtual ~MultiLevelStore();

	virtual const char *get(const char *key, unsigned int numElm = 0) const;
	template<typename T>
	T get(const char *key, unsigned int numElm = 0) const;
	virtual const char *get(unsigned int numKey) const;
	template<typename T>
	T get(unsigned int numKey) const;
	virtual const char *getKey(unsigned int numKey) const;
	virtual IMultiLevelStore *getLevel(const char *key, unsigned int numElm = 0) const;
	virtual IMultiLevelStore *getLevel(unsigned int numKey) const;
	virtual const char *getLevelKey(unsigned int numKey) const;

	virtual unsigned int getSize() const;
	virtual unsigned int getSize(const char *key) const;
	virtual unsigned int getNumLevels() const;
	virtual unsigned int getNumLevels(const char *key) const;

	virtual void add(const char *key, const char *value);
	template<typename T>
	void add(const char *key, T value);
	virtual IMultiLevelStore *addLevel(const char *key);

private:
	bool checkKey(const std::string &key) const;

	std::multimap<std::string, std::string> mData;
	std::multimap<std::string, std::unique_ptr<MultiLevelStore>> mLevels;
};

template<typename T>
T MultiLevelStore::get(const char *key, unsigned int numElm) const{
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
T MultiLevelStore::get(unsigned int numKey) const{
	if(numKey >= mData.size()) throw MaudioException("numKey out of range");
	auto iter = mData.begin();
	while(iter != mData.end() && numKey != 0){
		iter++;
		numKey--;
	}
	return string_to<T>(iter->second);
}

template<typename T>
void MultiLevelStore::add(const char *key, T value){
	std::string tmpKey(key);
	if(!checkKey(tmpKey)) return;
	mData.insert(std::make_pair(tmpKey, std::to_string(value)));
	return;
}

} // maudio

#endif // MAUDIO_MULTLEVELISTORE




