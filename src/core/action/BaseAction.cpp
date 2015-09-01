/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/action/BaseAction.hpp"

namespace maudio{

BaseAction::~BaseAction(){
	for(unsigned int i = 0; i < mInputs.size(); i++){
		removeInput(i);
	}
	return;
}

void BaseAction::deleteData(IAudioBuffer *data) noexcept{
	if(data) delete data;
	return;
}

void BaseAction::deleteData(IAudioInfo *data) noexcept{
	if(data) delete data;
	return;
}

void BaseAction::deleteData(ISample *data) noexcept{
	if(data) delete data;
	return;
}

void BaseAction::addInput(IAction *input, int slot){
	if(slot < 0 && (MaxInputs() < 0 || NumInputs() < MaxInputs())){
		mInputs.push_back(input);
	}
	else if(slot < MaxInputs() || MaxInputs() < 0){
		removeInput(slot);
		if((unsigned int)slot  >= mInputs.size()){
			mInputs.resize(slot + 1);
		}
		mInputs[slot] = input;
	}
	else{
		return; // fail
	}
	input->addObserver(this);
	return;
}

void BaseAction::removeInput(IAction *input){
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i] == input) removeInput(i);
	}
	return;
}

void BaseAction::removeInput(int slot){
	if((unsigned int)slot >= mInputs.size()) return;
	if(InputOk(slot)) mInputs[slot]->removeObserver(this);
	mInputs[slot] = NULL;
	mInputs.erase(mInputs.begin() + slot);
	return;
}

int BaseAction::NumInputs() const{
	/*int ret = 0;
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i]) ret++;
	}
	return ret;*/
	return mInputs.size();
}

IPropertyManager *BaseAction::getProperties(){
	return &mProperties;
}

IControl *BaseAction::getControl(){
	return NULL;
}

bool BaseAction::checkCompatible(IAudioInfo *info){
	if(!info) return false;
	return true;
}

void BaseAction::notify(const IObservable *origin, NoticeType type, const char *message){
	if(type == ON_DELETE){
		if(!origin) return;
		for(unsigned int i = 0; i < mInputs.size(); i++){
			if(!mInputs[i]) continue;
			if(mInputs[i]->getObservableID() == origin->getObservableID()){
				removeInput(i);
			}
		}
	}
	if(type == ON_CHANGE){
	}
	return;
}

bool BaseAction::InputOk(unsigned int slot){
	if(mInputs.size() > slot && mInputs[slot]) return true;
	return false;
}

sptr<IAudioBuffer> BaseAction::getFromSlot(unsigned int slot, unsigned long pos, unsigned int length){
	if(mInputs.size() < slot || !mInputs[slot]){
		return NULL;
	}
	return sptr<IAudioBuffer>(mInputs[slot]->get(pos, length), mInputs[slot]);
}

sptr<IAudioInfo> BaseAction::getInfoFromSlot(unsigned int slot){
	if(mInputs.size() < slot || !mInputs[slot]){
		return NULL;
	}
	return sptr<IAudioInfo>(mInputs[slot]->getInfo(), mInputs[slot]);
}

sptr<ISample> BaseAction::getSampleFromBuffer(unsigned int numSample, sptr<IAudioBuffer> buffer){
	if(!buffer){
		return NULL;
	}
	sptr<ISample> ret(buffer->get(numSample), buffer.getActionDeleter());
	return ret;
}

} // maudio



