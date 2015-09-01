/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PLUGINMANAGER
#define MAUDIO_PLUGINMANAGER

#include "core/pluginmanager/PluginLoader.hpp"
#include "core/action/IAction.hpp"
#include "core/util/plugin_ptr.hpp"
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
	plugin_ptr<IAction> createInstance(unsigned int plugin);
	plugin_ptr<IAction> createInstance(const char *plugin);

private:
	PluginManager();
	~PluginManager();
	PluginManager(const PluginManager&) = delete;
	void operator=(const PluginManager&) = delete;

	int nameToNum(const char *name);

	std::vector<std::shared_ptr<PluginLoader<IAction>>> mPlugins;
};

} // maudio

#endif // MAUDIO_PLUGINMANAGER




