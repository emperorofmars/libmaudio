/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/pluginmanager/PluginManager.hpp"

namespace maudio{

PluginManager::PluginManager(){
	return;
}

PluginManager::~PluginManager(){
	return;
}

PluginManager *PluginManager::Instance(){
	static PluginManager mPluginManager;
	return &mPluginManager;
}

void PluginManager::readConfig(const IMultiStore &conf){
	return;
}

void PluginManager::addPlugin(const char *path){
	std::shared_ptr<PluginLoader<IAction>> tmp(new PluginLoader<IAction>(path));
	if(tmp->loaded()){
		mPlugins.push_back(tmp);
	}
	return;
}

std::vector<std::string> PluginManager::listPlugins(){
	std::vector<std::string> ret;
	for(unsigned int i = 0; i < mPlugins.size(); i++){
		ret.push_back(mPlugins[i]->getName());
	}
	return ret;
}

plugin_ptr<IAction> PluginManager::createInstance(unsigned int plugin){
	if(plugin >= mPlugins.size()) throw MaudioException("Out of Bounds!");
	plugin_ptr<IAction> ret;
	ret.reset(mPlugins[plugin]->createInstance(), mPlugins[plugin].get());
	return ret;
}

plugin_ptr<IAction> PluginManager::createInstance(const char *plugin){
	int index = nameToNum(plugin);
	if(index < 0) throw MaudioException("Invalid Name!");
	if((unsigned int)index >= mPlugins.size()) throw MaudioException("Out of Bounds!");
	plugin_ptr<IAction> ret;
	ret.reset(mPlugins[index]->createInstance(), mPlugins[index].get());
	return ret;
}

int PluginManager::nameToNum(const char *name){
	for(unsigned int i = 0; i < mPlugins.size(); i++){
		if(mPlugins[i]->getName() == std::string(name)) return i;
	}
	return -1;
}

} // maudio



