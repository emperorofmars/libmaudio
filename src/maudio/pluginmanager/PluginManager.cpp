/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/pluginmanager/PluginManager.hpp"
#include "maudio/store/ConfigManager.hpp"
#include "maudio/store/StoreReader.hpp"
#include "maudio/util/TypeIdConverter.hpp"
#include "maudio/MaudioPaths.hpp"

namespace maudio{

PluginManager::PluginManager(){
	try{
		const char *searchpath = ConfigManager::Instance()->getConfig()->get("pluginsearchpath");
		if(searchpath) addSearchPath(searchpath);
		const char *path = ConfigManager::Instance()->getConfig()->get("pluginconf");
		if(path) parseConfig(path);
	}
	catch(std::exception &e){
	}
	
	try{
		const char *tmp = Paths::getUserPluginDir();
		if(tmp) addSearchPath(tmp);
		const char *path = Paths::getUserPluginConfigFile();
		if(path) parseConfig(path);
	}
	catch(std::exception &e){
	}
	
	if(!Paths::getPortable()){
		unsigned int i = 0;
		const char *tmpspath = NULL;
		while((tmpspath = Paths::getSystemPluginDir(i)) != NULL){
			addSearchPath(tmpspath);
			i++;
		}
		i = 0;
		tmpspath = NULL;
		while((tmpspath = Paths::getSystemPluginConfigFile(i)) != NULL){
			try{
				parseConfig(tmpspath);
			}
			catch(std::exception &e){
			}
		}
	}
	return;
}

PluginManager::~PluginManager(){
	return;
}

PluginManager *PluginManager::Instance(){
	static PluginManager mPluginManager;
	return &mPluginManager;
}

void PluginManager::parseConfig(const char *path){
	if(!path) throw MaudioException("invalid path!");
	StoreReader<IMultiStore> reader;
	try{
		readConfig(reader.readFile(path));
	}
	catch(std::exception &e){
	}
	return;
}

void PluginManager::readConfig(const IMultiStore *conf){
	if(!conf) throw MaudioException("invalid store!");
	for(unsigned int i = 0; i < conf->getSize("plugin"); i++){
		try{
			addPlugin(conf->get("plugin", i));
		}
		catch(std::exception &e){
		}
	}
	return;
}

void PluginManager::addSearchPath(const char *path){
	if(path) mSearchPaths.push_back(std::string(path));
	return;
}

std::vector<std::string> PluginManager::SearchPaths(){
	return mSearchPaths;
}

void PluginManager::addPlugin(const char *name){
	if(!name) throw MaudioException("invalid name!");
	std::string sname(name);
	
	std::shared_ptr<PluginLoader<IAction>> tmp;
	if((sname.size() > 0 && sname[0] == '/') ||
		(sname.size() > 1 && sname[0] == '.' && sname[1] == '/'))
	{
		tmp.reset(new PluginLoader<IAction>(sname.c_str()));
	}
	else{
		for(unsigned int i = 0; i < mSearchPaths.size(); i++){
			std::string path(mSearchPaths[i]);
			path.append(sname);
			tmp.reset(new PluginLoader<IAction>(path.c_str()));
			if(tmp) break;
		}
	}
	if(tmp->loaded()){
		if(checkNameCollisions(sname) || checkNameCollisions(tmp->getName())){
			throw MaudioException("plugin name collision!");
		}
		mPlugins.push_back(tmp);
	}
	else throw MaudioException("loading plugin failed!");
	return;
}

std::vector<std::string> PluginManager::listPlugins(){
	std::vector<std::string> ret;
	for(unsigned int i = 0; i < mPlugins.size(); i++){
		ret.push_back(mPlugins[i]->getName());
	}
	return ret;
}

sptr<IAction> PluginManager::createInstance(unsigned int plugin){
	if(plugin >= mPlugins.size()) throw MaudioException("Out of Bounds!");
	sptr<IAction> ret;
	ret.reset(mPlugins[plugin]->createInstance(), mPlugins[plugin].get());
	return ret;
}

sptr<IAction> PluginManager::createInstance(const char *plugin){
	int index = nameToNum(std::string(plugin));
	if(index < 0) throw MaudioException("Invalid Name!");
	if((unsigned int)index >= mPlugins.size()) throw MaudioException("Out of Bounds!");
	sptr<IAction> ret;
	ret.reset(mPlugins[index]->createInstance(), mPlugins[index].get());
	
	TypeIdConverter::addType(typeid(*ret), mPlugins[index]->getName().c_str());
	return ret;
}

int PluginManager::nameToNum(std::string name){
	for(unsigned int i = 0; i < mPlugins.size(); i++){
		if(mPlugins[i]->getName() == std::string(name)) return i;
	}
	return -1;
}

bool PluginManager::checkNameCollisions(std::string name){
	for(unsigned int i = 0; i < mPlugins.size(); i++){
		if(mPlugins[i]->getName() == name) return true;
	}
	return false;
}

} // maudio



