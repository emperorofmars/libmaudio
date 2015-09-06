/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_KEYVALUESTORE
#define MAUDIO_KEYVALUESTORE

#include "maudio/store/IKeyValueStore.hpp"
#include "maudio/util/Util.hpp"
#include "maudio/util/AudioException.hpp"
#include <string>
#include <unordered_map>

namespace maudio{

class KeyValueStore : public IKeyValueStore{
public:
	KeyValueStore();
	virtual ~KeyValueStore();

	virtual const char *get(const char *key) const;
	std::string get(const std::string &key) const;
	template<typename T>
	T get(const std::string &key) const;

	virtual const char *get(unsigned int numKey) const;
	template<typename T>
	T get(unsigned int numKey) const;

	virtual const char *getKey(unsigned int numKey) const;

	unsigned int getSize() const;

	virtual void set(const char *key, const char *value);
	void set(const std::string &key, const std::string &value);
	template<typename T>
	void set(const std::string &key, T value);

	void operator=(IKeyValueStore &data);

protected:
	bool checkKey(const std::string &key) const;

	std::unordered_map<std::string, std::string> mData;
};

template<typename T>
T KeyValueStore::get(const std::string &key) const{
	try{
		return string_to<T>(mData.at(key));
	}
	catch(std::exception &e){
		throw e;
	}
}

template<typename T>
T KeyValueStore::get(unsigned int numKey) const{
	try{
		if(numKey >= mData.size()) throw MaudioException("maudio: numKey out of range");
		auto iter = mData.begin();
		while(iter != mData.end() && numKey > 0){
			iter++;
			numKey--;
		}
		return string_to<T>(iter->second);
	}
	catch(std::exception &e){
		throw e;
	}
}

template<typename T>
void KeyValueStore::set(const std::string &key, T value){
	if(!checkKey(key)) return;
	try{
		mData[key] = std::to_string(value);
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

} // maudio

#endif // MAUDIO_KEYVALUESTORE









