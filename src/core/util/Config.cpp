/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/Config.hpp"
#include "core/util/AudioException.hpp"
#include <fstream>

#include <iostream>

namespace maudio{

Config::Config(){
}

Config::~Config(){
}

void Config::parseFile(const std::string &file){
	std::ifstream ifile(file);
	if(!ifile.good()) throw MaudioException("maudio: cant open file");

	std::string line;
	while(std::getline(ifile, line)){
		try{
			parseLine(line);
		}
		catch(std::exception &e){
		}
	}
	mFile = file;
	return;
}

void Config::saveFile() const{
	saveFile(mFile);
	return;
}

void Config::saveFile(const std::string &file) const{
	std::ofstream ofile(file);
	if(!ofile.good()) return;
	ofile << "# maudio config file" << std::endl;
	for(auto iter = mData.begin(); iter != mData.end(); iter ++){
		ofile << iter->first << " " << iter->second << std::endl;
	}
	return;
}

std::string Config::get(const std::string &key) const{
	return mData.at(key);
}

template<>
std::string Config::get(const std::string &key) const{
	try{
		return mData.at(key);
	}
	catch(std::exception &e){
		throw e;
	}
}

void Config::set(const std::string &key, const std::string &value){
	if(!checkKey(key)) return;
	mData[key] = value;
	return;
}

template<>
void Config::set(const std::string &key, std::string value){
	if(!checkKey(key)) return;
	mData[key] = value;
	return;
}

bool Config::checkKey(const std::string &key) const{
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] == ' ') return false;
	}
	return true;
}

void Config::parseLine(std::string &line){
	while(line.size() > 0 && (line[0] == ' ' || line[0] == '\t')){
		line.erase(0);
	}
	if(line.size() == 0 || line[0] == '\n' || line[0] == '\0' || line[0] == '#'){
		return;
	}

	std::string key = line.substr(0, line.find_first_of(' '));
	std::string value = line.substr(line.find_first_of(' ') + 1, line.size());

	try{
		set(key, value);
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

void Config::setDefaults(){
	set("PlayerQueueSize", 1024 * 8);
	set("SinkBufferSize", 1024 * 8);
    return;
}

} // maudio



