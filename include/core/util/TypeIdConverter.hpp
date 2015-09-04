/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_TYPEIDCONVERTER
#define MAUDIO_TYPEIDCONVERTER

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <string>

namespace maudio{

class TypeIdConverter{
public:
	static const char *getName(std::type_index type);
	
private:
	static bool addType(std::type_index type, const char *name);
	static void removeType(const char *name);
	
	static std::unordered_map<std::type_index, std::string> mIndex;
	
	friend class PluginManager;
};

} // maudio

#endif // MAUDIO_TYPEIDCONVERTER




