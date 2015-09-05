/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/scene/Project.hpp"
#include "core/serializer/SerializerInfo.hpp"
#include "core/util/SharedLockGuard.hpp"
#include "core/util/AudioException.hpp"
#include <fstream>

namespace maudio{

Project::Project(const char *name){
	setName(name);
	mSaveFile = mName;
	return;
}

Project::~Project(){
}

void Project::setName(const char *name){
	lock_guard lock(mMutex);
	mName = name;
	return;
}

const char *Project::getName() const{
	shared_lock_guard lock(mMutex);
	return mName.c_str();
}

void Project::addScene(std::shared_ptr<Scene> scene){
	lock_guard lock(mMutex);
	if(!scene) throw MaudioException("invalid scene!");
	if(getSceneNum(scene->getName()) >= 0) throw MaudioException("scene with same name already exists!");
	mScenes.push_back(scene);
	return;
}

void Project::removeScene(unsigned int num){
	lock_guard lock(mMutex);
	if(num >= mScenes.size()) throw MaudioException("out of range!");
	mScenes.erase(mScenes.begin() + num);
	return;
}

void Project::removeScene(const char *name){
	lock_guard lock(mMutex);
	int num = getSceneNum(name);
	if(num < 0)  throw MaudioException("invalid name!");
	mScenes.erase(mScenes.begin() + num);
	return;
}

std::shared_ptr<Scene> Project::getScene(unsigned int num) const{
	shared_lock_guard lock(mMutex);
	if(num >= mScenes.size()) throw MaudioException("out of range!");
	return mScenes[num];
}

std::shared_ptr<Scene> Project::getScene(const char *name) const{
	shared_lock_guard lock(mMutex);
	int num = getSceneNum(name);
	if(num < 0)  throw MaudioException("invalid name!");
	return mScenes[num];
}

unsigned int Project::getNumScenes() const{
	shared_lock_guard lock(mMutex);
	return mScenes.size();
}

void Project::save() const{
	shared_lock_guard lock(mMutex);
	if(mPreservePrevious){
		std::ifstream prevIn(mSaveFile);
		if(prevIn.is_open()){
			std::ofstream prevOut(std::string(mSaveFile).append(".previous"));
			if(prevOut.is_open()){
				std::string line;
				while(std::getline(prevIn, line)){
					prevOut << line << std::endl;
				}
				prevOut.close();
			}
			prevIn.close();
		}
	}
	
	std::shared_ptr<ISerializer> serializer = SerializerInfo::getDefaultSerializer();
	serializer->setName(mName.c_str());
	for(unsigned int i = 0; i < mScenes.size(); i++){
		serializer->addScene(mScenes[i]);
	}
	serializer->writeFile(mSaveFile.c_str());
	return;
}

void Project::load(const char *file){
	lock_guard lock(mMutex);
	mScenes.clear();
	
	std::shared_ptr<ISerializer> serializer = SerializerInfo::getSerializer(file);
	serializer->parseFile(file);
	
	mName = serializer->getName();
	mSaveFile = file;
	mScenes = serializer->getScenes();
	
	return;
}

void Project::setSaveFile(const char *file){
	lock_guard lock(mMutex);
	mSaveFile = file;
	return;
}

const char *Project::getSaveFile() const{
	shared_lock_guard lock(mMutex);
	return mSaveFile.c_str();
}

void Project::setPreservePrevious(bool preserve){
	lock_guard lock(mMutex);
	mPreservePrevious = preserve;
	return;
}

bool Project::getPreservePrevious() const{
	shared_lock_guard lock(mMutex);
	return mPreservePrevious;
}

void Project::readConfig(const IKeyValueStore *conf){
	lock_guard lock(mMutex);
	if(!conf) return;
	for(unsigned int i = 0; i < mScenes.size(); i++){
		try{
			mScenes[i]->readConfig(conf);
		}
		catch(std::exception &e){
		}
	}
	return;
}

int Project::getSceneNum(const char *name) const{
	shared_lock_guard lock(mMutex);
	if(!name) return -1;
	std::string sname(name);
	for(unsigned int i = 0; i < mScenes.size(); i++){
		if(mScenes[i] && std::string(mScenes[i]->getName()) == name) return i;
	}
	return -1;
}

} // maudio



