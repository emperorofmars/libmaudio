/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_CONFIG
#define MAUDIO_CONFIG

#include "core/util/Util.hpp"
#include <string>
#include <unordered_map>

namespace maudio{

class Config{
public:
	Config();
	~Config();

	void parseFile(const std::string &file);
	void saveFile() const;
	void saveFile(const std::string &file) const;

	std::string get(const std::string &key) const;
	template<typename T>
	T get(const std::string &key) const;

	void set(const std::string &key, const std::string &value);
	template<typename T>
	void set(const std::string &key, T value);

	void setDefaults();

private:
	bool checkKey(const std::string &key) const;
	void parseLine(std::string &line);

	std::string mFile;
	std::unordered_map<std::string, std::string> mData;
};

template<typename T>
T Config::get(const std::string &key) const{
	try{
		return string_to<T>(mData.at(key));
	}
	catch(std::exception &e){
		throw e;
	}
}

template<typename T>
void Config::set(const std::string &key, T value){
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

#endif // MAUDIO_CONFIG









