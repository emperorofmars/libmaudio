/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/serializer/SerializerInfo.hpp"
#include "core/serializer/TXTSerializer.hpp"
#include <fstream>

namespace maudio{

std::shared_ptr<ISerializer> SerializerInfo::getSerializer(const char *file){
	if(!file) return NULL;
	std::ifstream stream(file);
	if(!stream.is_open()) return NULL;
	
	std::string line;
	while(std::getline(stream, line)){
		if(line == "|TXTSerializer") return std::make_shared<TXTSerializer>();
	}
	
	return NULL;
}

std::shared_ptr<ISerializer> SerializerInfo::getDefaultSerializer(){
	return std::make_shared<TXTSerializer>();
}

} // maudio



