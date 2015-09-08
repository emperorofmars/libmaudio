/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_CONFIGMANAGER
#define MAUDIO_CONFIGMANAGER

#include "maudio/store/KeyValueStore.hpp"
#include <string>

namespace maudio{

class ConfigManager{
public:
	static ConfigManager* Instance();

	void setConfigPath(const char *path);
	const char *getConfigPath() const;

	const IKeyValueStore *getConfig() const;

	IKeyValueStore *manipulate();

private:
	ConfigManager();
	~ConfigManager();
	ConfigManager(const ConfigManager&) = delete;
	void operator=(const ConfigManager&) = delete;

	bool checkFile(const char *path) const;
	void loadFromFile(const char *path);
	void setDefaults();

	std::string mPath;
	KeyValueStore mConfig;
};

} // maudio

#endif // MAUDIO_CONFIGMANAGER









