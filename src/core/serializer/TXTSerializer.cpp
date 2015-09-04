/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/serializer/TXTSerializer.hpp"
#include "core/util/AudioException.hpp"

#include <iostream>

namespace maudio{


TXTSerializer::TXTSerializer(const char *name){
	setName(name);
}

TXTSerializer::~TXTSerializer(){
}

void TXTSerializer::setName(const char *name){
	mName = name;
	return;
}

const char *TXTSerializer::getName() const{
	return mName.c_str();
}

bool TXTSerializer::addScene(std::shared_ptr<Scene> data){
	if(!data) return false;
	mScenes.push_back(data);
	return true;
}

std::vector<std::shared_ptr<Scene>> TXTSerializer::getScenes(const char *name){
	return mScenes;
}

void TXTSerializer::writeFile(const char *path){
	std::ofstream file(path);
	if(!file.is_open()) throw MaudioException("couldn't open file!");
	
	mStore.reset(new MultiLevelStore());
	
	for(unsigned int i = 0; i < mScenes.size(); i++){
		mScenes[i]->serialize(mStore->addLevel("scene"));
	}
	writeHeader(file);
	writeLevel(file, mStore.get());
	
	file.flush();
	return;
}

void TXTSerializer::parseFile(const char *path){
	//TODO
	return;
}

std::shared_ptr<IMultiLevelStore> TXTSerializer::getStore(){
	return mStore;
}

void TXTSerializer::writeHeader(std::ofstream &file){
	if(!file.is_open()) throw MaudioException("writing file failed!");
	//TODO
	file << "|maudio_project" << std::endl;
	file << "|name "  << mName << std::endl;
	//maudio version
	file << "|TXTSerializer" << std::endl;
	//filestandard version
	return;
}

void TXTSerializer::writeLevel(std::ofstream &file, IMultiLevelStore *store, unsigned int indentLevel){
	if(!store || !file.is_open()) throw MaudioException("writing file failed!");
	writeCurrentLevel(file, store, indentLevel);
	
	for(unsigned int i = 0; i < store->getNumLevels(); i++){
		//std::cerr << "writeLevel: " << indentLevel << " : " << i << std::endl;
		file << printIndent(indentLevel) << "!level " << store->getLevelKey(i) << std::endl;
		writeLevel(file, store->getLevel(i), indentLevel + 1);
		file << printIndent(indentLevel) << "!end" << std::endl;
		//std::cerr << "writeLevel END" << std::endl;
	}
	return;
}

void TXTSerializer::writeCurrentLevel(std::ofstream &file, IMultiLevelStore *store, unsigned int indentLevel){
	if(!store || !file.is_open()) throw MaudioException("writing file failed!");
	
	if(store->getSize() == 0) return;
	for(unsigned int i = 0; i < store->getSize(); i++){
		const char *key = store->getKey(i);
		const char *value = store->get(i);
		if(!key || !value) continue;
		file << printIndent(indentLevel) << key  << " " << value << std::endl;
	}
	return;
}

void TXTSerializer::readLevel(std::ifstream &file, IMultiLevelStore *store){
	//TODO
	return;
}

std::string TXTSerializer::printIndent(unsigned int indentLevel){
	std::string ret;
	for(unsigned int ind = 0; ind < indentLevel; ind++){
		ret += '\t';
	}
	return ret;
}

} // maudio



