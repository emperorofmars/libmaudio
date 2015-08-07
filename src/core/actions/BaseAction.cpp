/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/actions/BaseAction.hpp"

namespace maudio{

BaseAction::~BaseAction(){
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i] != NULL){
			delete mInputs[i];
			mInputs[i] = NULL;
		}
	}
	return;
}

void BaseAction::addSocket(ISocket *socket, int slot){
	if(slot < 0 && MaxInputs() < 0) mInputs.push_back(socket);
	else if((unsigned int)slot < mInputs.size() && slot < MaxInputs()){
		if(mInputs[slot] != NULL){
			delete mInputs[slot];
			mInputs[slot] = NULL;
		}
		mInputs[slot] = socket;
	}
	return;
}

void BaseAction::removeSocket(int slot){
	if((unsigned int)slot >= mInputs.size()) return;
	if(mInputs[slot] != NULL){
		delete mInputs[slot];
		mInputs[slot] = NULL;
	}
	return;
}

int BaseAction::NumInputs() const{
	return mInputs.size();
}

IPropertyManager *BaseAction::getProperties(){
	return &mProperties;
}


} // maudio


