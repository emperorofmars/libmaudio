/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/MaudioPaths.hpp"
#include <fstream>

#include <iostream>

#if defined(unix) || defined(__unix__) || defined(__unix)
	#include <unistd.h>
	#include <sys/types.h>
	#include <pwd.h>
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64)
//
#endif

namespace maudio{

std::string Paths::mUserConfigDir;
std::string Paths::mUserPluginDir;
std::string Paths::mUserConfigFile;
std::string Paths::mUserPluginConfigFile;

std::vector<std::string> Paths::mSystemConfigDirs;
std::vector<std::string> Paths::mSystemPluginDirs;
std::vector<std::string> Paths::mSystemConfigFiles;
std::vector<std::string> Paths::mSystemPluginConfigFiles;

bool Paths::mSet = false;


bool Paths::getPortable(){
	return MAUDIO_PORTABLE;
}

const char *Paths::getUserConfigDir(){
	setup();
	if(mUserConfigDir.size() == 0) return NULL;
	return mUserConfigDir.c_str();
}

const char *Paths::getUserPluginDir(){
	setup();
	if(mUserPluginDir.size() == 0) return NULL;
	return mUserPluginDir.c_str();
}

const char *Paths::getUserConfigFile(){
	setup();
	if(mUserConfigFile.size() == 0) return NULL;
	return mUserConfigFile.c_str();
}

const char *Paths::getUserPluginConfigFile(){
	setup();
	if(mUserPluginConfigFile.size() == 0) return NULL;
	return mUserPluginConfigFile.c_str();
}

const char *Paths::getSystemConfigDir(unsigned int num){
	setup();
	if(getPortable()) return NULL;
	if(num >= mSystemConfigDirs.size()) return NULL;
	return mSystemConfigDirs[num].c_str();
}

const char *Paths::getSystemPluginDir(unsigned int num){
	setup();
	if(getPortable()) return NULL;
	if(num >= mSystemPluginDirs.size()) return NULL;
	return mSystemPluginDirs[num].c_str();
}

const char *Paths::getSystemConfigFile(unsigned int num){
	setup();
	if(getPortable()) return NULL;
	if(num >= mSystemConfigFiles.size()) return NULL;
	return mSystemConfigFiles[num].c_str();
}

const char *Paths::getSystemPluginConfigFile(unsigned int num){
	setup();
	if(getPortable()) return NULL;
	if(num >= mSystemPluginConfigFiles.size()) return NULL;
	return mSystemPluginConfigFiles[num].c_str();
}

void Paths::setup(){
	if(!mSet){
		if(MAUDIO_PORTABLE == 1){
			mUserConfigDir = MAUDIO_PORTABLE_CONFIGDIR;
			mUserPluginDir = MAUDIO_PORTABLE_PLUGINDIR;
			if(mUserConfigDir.size() > 0 && mUserConfigDir[mUserConfigDir.size() - 1] != '/'){
				mUserConfigDir.append("/");
			}
			if(mUserPluginDir.size() > 0 && mUserPluginDir[mUserPluginDir.size() - 1] != '/'){
				mUserPluginDir.append("/");
			}
		}
#if defined(unix) || defined(__unix__) || defined(__unix)
		else{
			//get xdg home directories
			const char *userconfigdir = getenv("XDG_CONFIG_HOME");
			const char *userplugindir = getenv("XDG_DATA_HOME");
			//if those arent set
			if(!userconfigdir || !userplugindir){
				struct passwd *pw = getpwuid(getuid());
				userconfigdir = pw->pw_dir;
				userplugindir = pw->pw_dir;
			}
			//ensure '/' cahracter at the end
			mUserConfigDir = userconfigdir;
			if(mUserConfigDir.size() > 0 && mUserConfigDir[mUserConfigDir.size() - 1] != '/'){
				mUserConfigDir.append("/");
			}
			mUserPluginDir = userplugindir;
			if(mUserPluginDir.size() > 0 && mUserPluginDir[mUserPluginDir.size() - 1] != '/'){
				mUserPluginDir.append("/");
			}
			if(userconfigdir && userplugindir){
				mUserConfigDir.append("maudio/config/");
				mUserPluginDir.append("maudio/plugins/");
			}
			else{
				mUserConfigDir.append(".maudio/config/");
				mUserPluginDir.append(".maudio/plugins/");
			}
			
			//get xdg system directories
			const char *systemconfigdir = getenv("XDG_CONFIG_DIRS");
			const char *systemplugindir = getenv("XDG_DATA_DIRS");
			if(!systemconfigdir || !systemplugindir){
				struct passwd *pw = getpwuid(getuid());
				systemconfigdir = pw->pw_dir;
				systemplugindir = pw->pw_dir;
			}
			//ensure '/' cahracter at the end and append maudio path
			std::string tmpconfdir(systemconfigdir);
			while(tmpconfdir.size() > 0){
				std::string tmp = tmpconfdir.substr(0, tmpconfdir.find_first_of(':'));
				if(tmp.size() > 0){
					tmpconfdir.erase(0, tmpconfdir.find_first_of(':'));
				}
				else{
					tmp = tmpconfdir.substr(0, tmpconfdir.size());
					tmpconfdir.erase(0, tmpconfdir.size());
					if(tmp.size() == 0) return;
				}
				if(tmp[tmp.size() - 1] != '/'){
					tmp.append("/");
				}
				tmp.append("maudio/config/");
				mSystemConfigDirs.push_back(tmp);
			}
			std::string tmpplugdir(systemplugindir);
			while(tmpplugdir.size() > 0){
				std::string tmp = tmpplugdir.substr(0, tmpplugdir.find_first_of(':'));
				if(tmp.size() > 0){
					tmpplugdir.erase(0, tmpplugdir.find_first_of(':'));
				}
				else{
					tmp = tmpplugdir.substr(0, tmpplugdir.size());
					tmpplugdir.erase(0, tmpplugdir.size());
					if(tmp.size() == 0) return;
				}
				if(tmp[tmp.size() - 1] != '/'){
					tmp.append("/");
				}
				tmp.append("maudio/plugins/");
				mSystemPluginDirs.push_back(tmp);
			}
		}
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64)
		else{
			//windows default dirs
		}
#endif
		//set user file paths if they exist
		std::string utmp1 = mUserConfigDir;
		utmp1.append(MAUDIO_DEFAULT_CONFIGFILE);
		std::ifstream ustream1(utmp1);
		if(ustream1.is_open()) mUserConfigFile = utmp1;
		
		std::string utmp2 = mUserConfigDir;
		utmp2.append(MAUDIO_DEFAULT_PLUGINCONFIGFILE);
		std::ifstream ustream2(utmp2);
		if(ustream2.is_open()) mUserPluginConfigFile = utmp1;
		
		//set system file paths if they exist
		if(!getPortable()){
			for(unsigned int i = 0; i < mSystemConfigDirs.size(); i++){
				std::string tmp1 = mSystemConfigDirs[i];
				tmp1.append(MAUDIO_DEFAULT_CONFIGFILE);
				std::ifstream stream1(tmp1);
				if(stream1.is_open()) mSystemConfigFiles.push_back(tmp1);
				
				std::string tmp2 = mSystemConfigDirs[i];
				tmp2.append(MAUDIO_DEFAULT_PLUGINCONFIGFILE);
				std::ifstream stream2(tmp2);
				if(stream2.is_open()) mSystemPluginConfigFiles.push_back(tmp2);
			}
		}
		
		mSet = true;
	}
	return;
}

} // maudio



