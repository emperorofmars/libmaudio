/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/Util.hpp"
#include <algorithm>

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

} // maudio







