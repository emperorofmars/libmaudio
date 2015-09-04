/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PLUGINMANAGER
#define MAUDIO_PLUGINMANAGER

#include "core/pluginmanager/PluginLoader.hpp"
#include "core/action/IAction.hpp"
#include "core/util/sptr.hpp"
#include "core/store/IMultiStore.hpp"
#include "core/util/AudioException.hpp"
#include <vector>
#include <memory>
#include <string>

namespace maudio{

class PluginManager{
public:
	static PluginManager *Instance();

	void parseConfig(const char *path);
	void readConfig(const IMultiStore *conf);

	void addPlugin(const char *path);
	std::vector<std::string> listPlugins();
	sptr<IAction> createInstance(unsigned int plugin);
	sptr<IAction> createInstance(const char *plugin);

private:
	PluginManager();
	~PluginManager();
	PluginManager(const PluginManager&) = delete;
	void operator=(const PluginManager&) = delete;

	int nameToNum(std::string name);
	bool checkNameCollisions(std::string name);
	
	std::vector<std::shared_ptr<PluginLoader<IAction>>> mPlugins;
};

} // maudio

#endif // MAUDIO_PLUGINMANAGER




