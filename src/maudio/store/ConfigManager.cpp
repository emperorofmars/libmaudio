/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/store/ConfigManager.hpp"
#include "maudio/store/StoreReader.hpp"
#include "maudio/util/sptr.hpp"
#include "maudio/util/AudioException.hpp"
#include "maudio/MaudioPaths.hpp"
#include <fstream>

namespace maudio{

ConfigManager* ConfigManager::Instance(){
	static ConfigManager mInstance;
	return &mInstance;
}

ConfigManager::ConfigManager(){
	setDefaults();
	unsigned int i = 0;
	const char *conf = NULL;
	while((conf = Paths::getSystemConfigFile(i)) != NULL){
		try{
			loadFromFile(conf);
		}
		catch(std::exception &e){
		}
	}
	const char *tmpfile = Paths::getUserConfigFile();
	if(tmpfile) mPath = tmpfile;
	try{
		if(checkFile(mPath.c_str())){
			loadFromFile(mPath.c_str());
		}
		else{
			mPath = "";
		}
	}
	catch(std::exception &e){
		mPath = "";
	}
}

ConfigManager::~ConfigManager(){
}

void ConfigManager::setConfigPath(const char *path){
	if(!path) throw MaudioException("invalid path!");
	if(checkFile(path)){
		loadFromFile(path);
		mPath = path;
	}
	return;
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
	if(!path) throw MaudioException("invalid path");
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
	mConfig.set("pluginconf", Paths::getUserPluginConfigFile());
	return;
}

} // maudio








