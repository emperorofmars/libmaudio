/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_CONFIGMANAGER
#define MAUDIO_CONFIGMANAGER

#define CONFIG_DEFAULT_PATH "maudio.conf"

#include "core/store/Config.hpp"
#include <string>

namespace maudio{

class ConfigManager{
public:
	static ConfigManager* Instance();

	void setConfigPath(const std::string &path);
	std::string getConfigPath() const;

	const Config &getConfig() const;

	Config &manipulate();

private:
	ConfigManager();
	~ConfigManager();
	ConfigManager(const ConfigManager&) = delete;
	void operator=(const ConfigManager&) = delete;

	bool checkFile(const std::string &path) const;
	void loadFromFile(const std::string &path);

	std::string mPath;
	Config mConfig;
};

} // maudio

#endif // MAUDIO_CONFIGMANAGER









