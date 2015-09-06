/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/TypeIdConverter.hpp"
#include "core/action/ErrorAction.hpp"
#include "extended/action/SinusGenerator.hpp"
#include "extended/action/TerminalPrinter.hpp"

namespace maudio{

std::unordered_map<std::type_index, std::string> TypeIdConverter::mIndex = {
	{typeid(ErrorAction), "ErrorAction"},
	{typeid(SinusGenerator), "SinusGenerator"},
	{typeid(TerminalPrinter), "TerminalPrinter"},
};

const char *TypeIdConverter::getName(std::type_index type){
	if(mIndex.find(type) == mIndex.end()) return NULL;
	return mIndex[type].c_str();
}

bool TypeIdConverter::addType(std::type_index type, const char *name){
	std::string strname(name);
	if(mIndex.find(type) != mIndex.end()) return false;
	for(auto iter = mIndex.begin(); iter != mIndex.end(); iter++){
		if(iter->second == strname) return false;
	}
	mIndex[type] = strname;
	return true;
}

void TypeIdConverter::removeType(const char *name){
	std::string strname(name);
	for(auto iter = mIndex.begin(); iter != mIndex.end(); iter++){
		if(iter->second == strname) mIndex.erase(iter);
	}
	return;
}

} // maudio



