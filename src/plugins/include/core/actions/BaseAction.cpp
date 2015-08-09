/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/actions/BaseAction.hpp"

namespace maudio{

BaseAction::~BaseAction(){
	for(unsigned int i = 0; i < mInputs.size(); i++){
		removeSocket(i);
	}
	return;
}

void BaseAction::deleteBuffer(IAudioBuffer *data) noexcept{
	if(data) delete data;
	return;
}

void BaseAction::deleteInfo(IAudioInfo *data) noexcept{
	if(data) delete data;
	return;
}

void BaseAction::deleteSample(ISample *data) noexcept{
	if(data) delete data;
	return;
}

void BaseAction::addSocket(ISocket *socket, int slot){
	if(slot < 0 && MaxInputs() < 0){
		mInputs.push_back(socket);
	}
	else if(slot < MaxInputs()){
		if((unsigned int)slot  >= mInputs.size()){
			mInputs.resize(slot + 1);
		}
		removeSocket(slot);
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

IControl *BaseAction::getControl(){
	return NULL;
}

} // maudio



