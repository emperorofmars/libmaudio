/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/Config.hpp"
#include "core/util/Util.hpp"
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

double Config::get_double(const std::string &key) const{
	try{
		return string_to<double>(mData.at(key));
	}
	catch(std::exception &e){
		throw e;
	}
}

long Config::get_long(const std::string &key) const{
	try{
		return string_to<long>(mData.at(key));
	}
	catch(std::exception &e){
		throw e;
	}
}

unsigned long Config::get_ulong(const std::string &key) const{
	try{
		return string_to<unsigned long>(mData.at(key));
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

void Config::set(const std::string &key, double value){
	if(!checkKey(key)) return;
	try{
		mData[key] = std::to_string(value);
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

void Config::set(const std::string &key, long value){
	if(!checkKey(key)) return;
	try{
		mData[key] = std::to_string(value);
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

void Config::set(const std::string &key, unsigned long value){
	if(!checkKey(key)) return;
	try{
		mData[key] = std::to_string(value);
	}
	catch(std::exception &e){
		throw e;
	}
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
	set("PlayerQueueSize", (unsigned long)4096);
	set("SinkBufferSize", (unsigned long)4096);
    return;
}

} // maudio



