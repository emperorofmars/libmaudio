/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_STOREREADER
#define MAUDIO_STOREREADER

#include "core/store/KeyValueStore.hpp"
#include "core/store/MultiStore.hpp"
#include "core/store/MultiLevelStore.hpp"
#include <string>
#include <istream>

#include <iostream>

namespace maudio{

template<typename T>
class StoreReader{
public:
	StoreReader();
	~StoreReader();

	T *readFile(const char *file);
	T *readStream(std::istream &stream);

private:
	void readLevel(std::istream &file, IMultiLevelStore *store);
	
	std::pair<std::string, std::string> parseLine(std::string &line);
};


template<>
IKeyValueStore *StoreReader<IKeyValueStore>::readFile(const char *file);
template<>
IKeyValueStore *StoreReader<IKeyValueStore>::readStream(std::istream &stream);
template<>
IMultiStore *StoreReader<IMultiStore>::readFile(const char *file);
template<>
IMultiStore *StoreReader<IMultiStore>::readStream(std::istream &stream);
template<>
IMultiLevelStore *StoreReader<IMultiLevelStore>::readFile(const char *file);
template<>
IMultiLevelStore *StoreReader<IMultiLevelStore>::readStream(std::istream &stream);
template<>
void StoreReader<IMultiLevelStore>::readLevel(std::istream &stream, IMultiLevelStore *store);


template<typename T>
StoreReader<T>::StoreReader(){
}

template<typename T>
StoreReader<T>::~StoreReader(){
}

template<typename T>
std::pair<std::string, std::string> StoreReader<T>::parseLine(std::string &line){
	std::pair<std::string, std::string> ret;

	while((line.size() > 0) && (line[0] == ' ' || line[0] == '\t')){
		line.erase(0, 1);
	}
	if(line.size() == 0 || line[0] == '\n' || line[0] == '\0' || line[0] == '#' || line[0] == '|'){
		throw MaudioException("error parsing line!");
	}

	ret.first = line.substr(0, line.find_first_of(' '));
	ret.second = line.substr(line.find_first_of(' ') + 1, line.size());

	return ret;
}

} // maudio

#endif // MAUDIO_STOREREADER




