/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "MaudioInfo.hpp"
#include "core/util/Util.hpp"
#include <string>

namespace maudio{


const char *getGitBranch(){
	return MAUDIO_GIT_BRANCH;
}

const char *getGitCommit(){
	return MAUDIO_GIT_COMMIT;
}

const char *getGitDescription(){
	return MAUDIO_GIT_DESCRIPTION;
}

const char *getVersionString(){
	return MAUDIO_VERSION;
}

int getVersionMajor(){
	std::string num(MAUDIO_VERSION);
	if(num.size() == 0 || num[0] != 'v' || num == "unknown"){
		return -1;
	}
	int ret = -1;
	try{
		num.erase(0, 1);
		ret = string_to<int>(num);
	}
	catch(std::exception &e){
		ret = -1;
	}
	return ret;
}

int getVersionMinor(){
	std::string num(MAUDIO_VERSION);
	if(num.size() == 0 || num[0] != 'v' || num == "unknown"){
		return -1;
	}
	int ret = -1;
	try{
		num.erase(0, num.find_first_of('.') + 1);
		ret = string_to<int>(num);
	}
	catch(std::exception &e){
		ret = -1;
	}
	return ret;
}

int getVersionPatch(){
	std::string num(MAUDIO_VERSION);
	if(num.size() == 0 || num[0] != 'v' || num == "unknown"){
		return -1;
	}
	int ret = -1;
	try{
		num.erase(0, num.find_first_of('.') + 1);
		num.erase(0, num.find_first_of('.') + 1);
		ret = string_to<int>(num);
	}
	catch(std::exception &e){
		ret = -1;
	}
	return ret;
}

} // maudio



