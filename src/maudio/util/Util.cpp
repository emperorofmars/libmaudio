/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/util/Util.hpp"
#include <algorithm>
#include <cstring>

namespace maudio{

double PositionToSeconds(unsigned long pos, unsigned int samplerate){
	return (double)pos / (double)samplerate;
}

unsigned long SecondsToPosition(double pos, unsigned int samplerate){
	return pos * samplerate;
}

template<>
bool string_to(const std::string &str){
	std::string tmp = str;
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	if(tmp == "true" || tmp == "1") return true;
	else return false;
}

template<>
int string_to(const std::string &str){
	try{return std::stoi(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
unsigned int string_to(const std::string &str){
	try{return std::stoul(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
long string_to(const std::string &str){
	try{return std::stol(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
unsigned long string_to(const std::string &str){
	try{return std::stoul(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
long long string_to(const std::string &str){
	try{return std::stol(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
unsigned long long string_to(const std::string &str){
	try{return std::stoull(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
float string_to(const std::string &str){
	try{return std::stof(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
double string_to(const std::string &str){
	try{return std::stod(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
long double string_to(const std::string &str){
	try{return std::stold(str);}
	catch(std::exception &e){
		throw e;
	}
}

template<>
const char *string_to(const std::string &str){
	char *ret = new char[str.size() + 1];
	strcpy(ret, str.c_str());
	return ret;
}

template<>
std::string string_to(const std::string &str){
	return str;
}

const char* to_chararray(bool value){
	if(value) return "true";
	return "false";
}

const char* to_chararray(int value){
	std::string tmp = std::to_string(value);
	char *ret = new char[tmp.size() + 1];
	strcpy(ret, tmp.c_str());
	return ret;
}

const char* to_chararray(unsigned int value){
	std::string tmp = std::to_string(value);
	char *ret = new char[tmp.size() + 1];
	strcpy(ret, tmp.c_str());
	return ret;
}

const char* to_chararray(long value){
	std::string tmp = std::to_string(value);
	char *ret = new char[tmp.size() + 1];
	strcpy(ret, tmp.c_str());
	return ret;
}

const char* to_chararray(unsigned long value){
	std::string tmp = std::to_string(value);
	char *ret = new char[tmp.size() + 1];
	strcpy(ret, tmp.c_str());
	return ret;
}

const char* to_chararray(float value){
	std::string tmp = std::to_string(value);
	char *ret = new char[tmp.size() + 1];
	strcpy(ret, tmp.c_str());
	return ret;
}

const char* to_chararray(double value){
	std::string tmp = std::to_string(value);
	char *ret = new char[tmp.size() + 1];
	strcpy(ret, tmp.c_str());
	return ret;
}

const char* to_chararray(long double value){
	std::string tmp = std::to_string(value);
	char *ret = new char[tmp.size() + 1];
	strcpy(ret, tmp.c_str());
	return ret;
}

const char* to_chararray(const char *value){
	if(!value) return "";
	char *ret = new char[strlen(value) + 1];
	strcpy(ret, value);
	return ret;
}

const char* to_chararray(std::string &value){
	char *ret = new char[value.size() + 1];
	strcpy(ret, value.c_str());
	return ret;
}

const char* to_chararray(std::string value){
	char *ret = new char[value.size() + 1];
	strcpy(ret, value.c_str());
	return ret;
}

} // maudio







