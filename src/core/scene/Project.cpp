/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/scene/Project.hpp"

namespace maudio{


Project::Project(const char *name){
	setName(name);
	return;
}

Project::~Project(){
}

void Project::setName(const char *name){
	mName = name;
	return;
}

const char *Project::getName() const{
	return mName.c_str();
}

void Project::addScene(std::shared_ptr<Scene> scene){
	return;
}

void Project::removeScene(unsigned int numi){
	return;
}

void Project::removeScene(const char *name){
	return;
}

void Project::getScene(unsigned int num){
	return;
}

void Project::getScene(const char *name){
	return;
}

void Project::save(){
	return;
}

void Project::load(const char *file){
	return;
}

void Project::setSaveFile(const char *file){
	mSaveFile = file;
	return;
}

void Project::setSaveHistory(unsigned int len){
	mSaveHistory = len;
	return;
}

const char *Project::getSaveFile(){
	return mSaveFile.c_str();
}

unsigned int Project::getSaveHistory(){
	return mSaveHistory;
}

void Project::readConfig(const IKeyValueStore *conf){
	return;
}

} // maudio



