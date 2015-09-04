/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/serializer/TXTSerializer.hpp"
#include "core/util/AudioException.hpp"
#include "core/store/StoreWriter.hpp"
#include "core/store/StoreReader.hpp"

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
	
	StoreWriter<IMultiLevelStore> writer;
	writer.writeStream(file, mStore.get());
	
	//writeLevel(file, mStore.get());
	
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

} // maudio



