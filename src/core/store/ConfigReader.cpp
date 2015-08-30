/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/store/ConfigReader.hpp"
#include "core/store/KeyValueStore.hpp"
#include "core/store/MultiStore.hpp"
#include "core/store/MultiLevelStore.hpp"
#include "core/util/AudioException.hpp"
#include <fstream>

namespace maudio{

template<>
IKeyValueStore *ConfigReader<IKeyValueStore>::readFile(const char *file){
	std::ifstream ifile(file);
	if(!ifile.good()) throw MaudioException("cant open file");

	IKeyValueStore *ret = new KeyValueStore();

	std::string line;
	while(std::getline(ifile, line)){
		try{
			std::pair<std::string, std::string> values = parseLine(line);
			ret->set(values.first.c_str(), values.second.c_str());
		}
		catch(std::exception &e){
		}
	}
	return ret;
}

template<>
IMultiStore *ConfigReader<IMultiStore>::readFile(const char *file){
	std::ifstream ifile(file);
	if(!ifile.good()) throw MaudioException("cant open file");

	IMultiStore *ret = new MultiStore();

	std::string line;
	while(std::getline(ifile, line)){
		try{
			std::pair<std::string, std::string> values = parseLine(line);
			ret->add(values.first.c_str(), values.second.c_str());
		}
		catch(std::exception &e){
		}
	}
	return ret;
}

template<>
IMultiLevelStore *ConfigReader<IMultiLevelStore>::readFile(const char *file){
	return NULL;
}

template<>
void ConfigReader<IKeyValueStore>::saveFile(const char *file, IKeyValueStore *config){
	return;
}

template<>
void ConfigReader<IMultiStore>::saveFile(const char *file, IMultiStore *config){
	return;
}

template<>
void ConfigReader<IMultiLevelStore>::saveFile(const char *file, IMultiLevelStore *config){
	return;
}

} // maudio



