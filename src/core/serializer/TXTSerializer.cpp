/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/serializer/TXTSerializer.hpp"
#include "core/store/StoreWriter.hpp"
#include "core/store/StoreReader.hpp"
#include "core/util/AudioException.hpp"

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

std::vector<std::shared_ptr<Scene>> TXTSerializer::getScenes() const{
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
	std::ifstream file(path);
	if(!file.is_open()) throw MaudioException("couldn't open file!");
	
	mName.clear();
	mStore.reset();
	mScenes.clear();
	
	if(!parseHeader(file)) throw MaudioException("invalid fileheader!");
	
	StoreReader<IMultiLevelStore> reader;
	mStore.reset(reader.readStream(file));
	
	for(unsigned int i = 0; i < mStore->getNumLevels("scene"); i++){
		std::shared_ptr<Scene> tmp(new Scene());
		tmp->deserialize(mStore->getLevel("scene", i));
		mScenes.push_back(tmp);
	}
	
	return;
}

std::shared_ptr<IMultiLevelStore> TXTSerializer::getStore() const{
	return mStore;
}

void TXTSerializer::writeHeader(std::ofstream &file) const{
	if(!file.is_open()) throw MaudioException("writing file failed!");
	//TODO
	file << "|maudio_project" << std::endl;
	file << "|name "  << mName << std::endl;
	//maudio version
	file << "|TXTSerializer" << std::endl;
	//filestandard version
	return;
}

bool TXTSerializer::parseHeader(std::ifstream &file){
	if(!file.is_open()) throw MaudioException("writing file failed!");
	//TODO
	std::string line;
	bool hasName = false, hasType = false, hasProject = false;
	while(std::getline(file, line)){
		if(line.size() > 1 && line[0] == '|'){
			if(line.substr(0, 15) == "|maudio_project"){
				hasProject = true;
			}
			else if(line.substr(0, 5) == "|name"){
				mName = line.substr(line.find_first_of(' ') + 1, line.size());
				hasName = true;
			}
			else if(line.substr(0, 14) == "|TXTSerializer"){
				hasType = true;
				break;
			}
		}
		else break;
	}
	if(hasName && hasProject && hasType) return true;
	return false;
}

} // maudio



