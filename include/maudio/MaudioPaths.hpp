/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PATHS
#define MAUDIO_PATHS

#include <string>
#include <vector>

#ifndef MAUDIO_PORTABLE
	#define MAUDIO_PORTABLE 0
#endif

#ifndef MAUDIO_PORTABLE_CONFIGDIR
	#define MAUDIO_PORTABLE_CONFIGDIR "res/config/"
#endif

#ifndef MAUDIO_PORTABLE_PLUGINDIR
	#define MAUDIO_PORTABLE_PLUGINDIR "res/plugins/"
#endif

#ifndef MAUDIO_SYSTEM_CONFIGDIR
	#define MAUDIO_SYSTEM_CONFIGDIR "maudio/config/"
#endif

#ifndef MAUDIO_SYSTEM_PLUGINDIR
	#define MAUDIO_SYSTEM_PLUGINDIR "maudio/plugins/"
#endif

#ifndef MAUDIO_DEFAULT_CONFIGDIR
	#define MAUDIO_DEFAULT_CONFIGDIR "maudio/config/"
#endif

#ifndef MAUDIO_DEFAULT_PLUGINDIR
	#define MAUDIO_DEFAULT_PLUGINDIR "maudio/plugins/"
#endif

#ifndef MAUDIO_DEFAULT_CONFIGFILE
	#define MAUDIO_DEFAULT_CONFIGFILE "maudio.conf"
#endif

#ifndef MAUDIO_DEFAULT_PLUGINCONFIGFILE
	#define MAUDIO_DEFAULT_PLUGINCONFIGFILE "plugins.conf"
#endif

namespace maudio{

class Paths{
public:
	static bool getPortable();
	
	static const char *getUserConfigDir();
	static const char *getUserPluginDir();
	static const char *getUserConfigFile();
	static const char *getUserPluginConfigFile();
	
	static const char *getSystemConfigDir(unsigned int num = 0);
	static const char *getSystemPluginDir(unsigned int num = 0);
	static const char *getSystemConfigFile(unsigned int num = 0);
	static const char *getSystemPluginConfigFile(unsigned int num = 0);
	
private:
	static void setup();
	
	static std::string mUserConfigDir;
	static std::string mUserPluginDir;
	static std::string mUserConfigFile;
	static std::string mUserPluginConfigFile;
	
	static std::vector<std::string> mSystemConfigDirs;
	static std::vector<std::string> mSystemPluginDirs;
	static std::vector<std::string> mSystemConfigFiles;
	static std::vector<std::string> mSystemPluginConfigFiles;
	
	static bool mSet;
};

} // maudio

#endif // MAUDIO_PATHS




