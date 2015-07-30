/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/store/ConfigManager.hpp"
#include "core/util/AudioException.hpp"
#include <fstream>

namespace maudio{

ConfigManager* ConfigManager::Instance(){
	static ConfigManager mInstance;
	return &mInstance;
}

ConfigManager::ConfigManager(){
	mConfig.setDefaults();
	mPath = CONFIG_DEFAULT_PATH;
	if(checkFile(mPath)){
		loadFromFile(mPath);
	}
	else{
		mPath = "";
	}
}

ConfigManager::~ConfigManager(){
}

void ConfigManager::setConfigPath(const std::string &path){
	if(checkFile(path)){
		loadFromFile(path);
		mPath = path;
	}
	throw MaudioException("maudio: invalid config path");
}

std::string ConfigManager::getConfigPath() const{
	return mPath;
}

const Config &ConfigManager::getConfig() const{
	return mConfig;
}

Config &ConfigManager::manipulate(){
	return mConfig;
}

bool ConfigManager::checkFile(const std::string &path) const{
	std::ifstream ifile(path);
	if(ifile.good()) return true;
	return false;
}

void ConfigManager::loadFromFile(const std::string &path){
	mConfig.parseFile(path);
	return;
}

} // maudio








