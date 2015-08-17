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

void BaseAction::addSocket(IAudioGetter *socket, int slot){
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
	mInputs[slot] = NULL;
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

action_ptr<IAudioBuffer> BaseAction::getFromSlot(unsigned int slot, unsigned long pos, unsigned int length){
	if(mInputs.size() < slot && !mInputs[slot]){
		return NULL;
	}
	return action_ptr<IAudioBuffer>(mInputs[slot]->get(pos, length), mInputs[slot]);
}

action_ptr<IAudioInfo> BaseAction::getInfoFromSlot(unsigned int slot){
	if(mInputs.size() < slot && !mInputs[slot]){
		return NULL;
	}
	return action_ptr<IAudioInfo>(mInputs[slot]->getInfo(), mInputs[slot]);
}

} // maudio



