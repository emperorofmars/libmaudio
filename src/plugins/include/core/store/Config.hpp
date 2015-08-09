/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_CONFIG
#define MAUDIO_CONFIG

#include "core/store/KeyValueStore.hpp"
#include "core/util/Util.hpp"
#include <string>
#include <unordered_map>

namespace maudio{

class Config : public KeyValueStore{
public:
	Config();
	~Config();

	void parseFile(const std::string &file);
	void saveFile() const;
	void saveFile(const std::string &file) const;

	void setDefaults();

private:
	void parseLine(std::string &line);

	std::string mFile;
};

} // maudio

#endif // MAUDIO_CONFIG









