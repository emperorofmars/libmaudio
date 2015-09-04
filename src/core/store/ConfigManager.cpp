/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/store/ConfigManager.hpp"
#include "core/store/StoreReader.hpp"
#include "core/util/sptr.hpp"
#include "core/util/AudioException.hpp"
#include <fstream>

namespace maudio{

ConfigManager* ConfigManager::Instance(){
	static ConfigManager mInstance;
	return &mInstance;
}

ConfigManager::ConfigManager(){
	setDefaults();
	mPath = CONFIG_DEFAULT_PATH;
	if(checkFile(mPath.c_str())){
		loadFromFile(mPath.c_str());
	}
	else{
		mPath = "";
	}
}

ConfigManager::~ConfigManager(){
}

void ConfigManager::setConfigPath(const char *path){
	if(checkFile(path)){
		loadFromFile(path);
		mPath = path;
	}
	throw MaudioException("invalid config path");
}

const char *ConfigManager::getConfigPath() const{
	return mPath.c_str();
}

const IKeyValueStore *ConfigManager::getConfig() const{
	return &mConfig;
}

IKeyValueStore *ConfigManager::manipulate(){
	return &mConfig;
}

bool ConfigManager::checkFile(const char *path) const{
	std::ifstream ifile(path);
	if(ifile.good()) return true;
	return false;
}

void ConfigManager::loadFromFile(const char *path){
	StoreReader<IKeyValueStore> reader;
	try{
		sptr<IKeyValueStore> tmp(reader.readFile(path));
		mConfig = *tmp;
	}
	catch(std::exception &e){
	}
	return;
}

void ConfigManager::setDefaults(){
	mConfig.set("pluginconf", "res/config/plugins.conf");
	mConfig.set("PlayerQueueSize", 1024 * 8);
	mConfig.set("SinkBufferSize", 1024 * 8);
	return;
}

} // maudio








