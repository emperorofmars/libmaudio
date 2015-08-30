/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_CONFIGREADER
#define MAUDIO_CONFIGREADER

#include <string>

namespace maudio{

template<typename T>
class ConfigReader{
public:
	ConfigReader();
	~ConfigReader();

	T *readFile(const char *file);
	void saveFile(const char *file, T *config);

private:
	std::pair<std::string, std::string> parseLine(std::string &line);
};

template<typename T>
ConfigReader<T>::ConfigReader(){
}

template<typename T>
ConfigReader<T>::~ConfigReader(){
}

template<typename T>
std::pair<std::string, std::string> ConfigReader<T>::parseLine(std::string &line){
	std::pair<std::string, std::string> ret;

	while(line.size() > 0 && (line[0] == ' ' || line[0] == '\t')){
		line.erase(0);
	}
	if(line.size() == 0 || line[0] == '\n' || line[0] == '\0' || line[0] == '#'){
		return ret;
	}

	ret.first = line.substr(0, line.find_first_of(' '));
	ret.second = line.substr(line.find_first_of(' ') + 1, line.size());

	return ret;
}

} // maudio

#endif // MAUDIO_CONFIGREADER




