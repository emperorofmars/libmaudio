/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/store/StoreReader.hpp"
#include "core/util/AudioException.hpp"
#include <fstream>

namespace maudio{

template<>
IKeyValueStore *StoreReader<IKeyValueStore>::readFile(const char *file){
	std::ifstream ifile(file);
	if(!ifile.good()) throw MaudioException("cant open file");

	return readStream(ifile);
}

template<>
IKeyValueStore *StoreReader<IKeyValueStore>::readStream(std::istream &stream){
	if(!stream.good()) throw MaudioException("invalid stream");
	IKeyValueStore *ret = new KeyValueStore();

	std::string line;
	bool correctType = false;
	while(std::getline(stream, line)){
		if(line == "|IKeyValueStore"){
			correctType = true;
			break;
		}
	}
	if(!correctType) throw MaudioException("invalid storetype");
	
	while(std::getline(stream, line)){
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
IMultiStore *StoreReader<IMultiStore>::readFile(const char *file){
	std::ifstream ifile(file);
	if(!ifile.good()) throw MaudioException("cant open file");
	
	return readStream(ifile);
}

template<>
IMultiStore *StoreReader<IMultiStore>::readStream(std::istream &stream){
	if(!stream.good()) throw MaudioException("invalid stream");
	IMultiStore *ret = new MultiStore();

	std::string line;
	bool correctType = false;
	while(std::getline(stream, line)){
		if(line == "|IMultiStore"){
			correctType = true;
			break;
		}
	}
	if(!correctType) throw MaudioException("invalid storetype");
	
	while(std::getline(stream, line)){
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
IMultiLevelStore *StoreReader<IMultiLevelStore>::readFile(const char *file){
	std::ifstream ifile(file);
	if(!ifile.good()) throw MaudioException("cant open file");
	
	return readStream(ifile);
}

template<>
IMultiLevelStore *StoreReader<IMultiLevelStore>::readStream(std::istream &stream){
	IMultiLevelStore *ret = new MultiLevelStore();
	if(!stream.good()) throw MaudioException("invalid stream");
	
	std::string line;
	bool correctType = false;
	while(std::getline(stream, line)){
		if(line == "|IMultiLevelStore"){
			correctType = true;
			break;
		}
	}
	if(!correctType) throw MaudioException("invalid storetype");
	
	readLevel(stream, ret);
	
	return ret;
}

template<>
void StoreReader<IMultiLevelStore>::readLevel(std::istream &stream, IMultiLevelStore *store){
	if(!store) throw MaudioException("invalid store");
	if(!stream.good()) throw MaudioException("invalid stream");
	
	std::string line;
	while(std::getline(stream, line)){
		try{
			std::pair<std::string, std::string> values = parseLine(line);
			if(values.first == "!level" && values.second.size() > 0){
				readLevel(stream, store->addLevel(values.second.c_str()));
			}
			else if(values.first == "!end"){
				return;
			}
			else if(values.first[0] == '!'){
				return;
			}
			else if(values.first.size() > 0 && values.second.size() > 0){
				store->add(values.first.c_str(), values.second.c_str());
			}
		}
		catch(std::exception &e){
		}
	}
	
	return;
}

} // maudio









