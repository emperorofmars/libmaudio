/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/action/BaseAction.hpp"

namespace maudio{

BaseAction::~BaseAction(){
	for(unsigned int i = 0; i < mInputs.size(); i++){
		removeInput(i);
	}
	return;
}

void BaseAction::setName(const char *name){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	mName = name;
	return;
}

const char *BaseAction::getName() const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return mName.c_str();
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

bool BaseAction::addInput(IAction *input, int slot){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(!input) return false;
	if(!checkCompatible(sptr<IAudioInfo>(input->getInfo()).get())) return false;
	if(checkCycles(input)) return false;

	if(slot < 0 && (MaxInputs() < 0 || (int)NumInputs() < MaxInputs())){
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
		return false;
	}
	input->addObserver(this);
	onAdd(slot);
	return true;
}

void BaseAction::removeInput(IAction *input){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i] == input) removeInput(i);
	}
	return;
}

void BaseAction::removeInput(int slot){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if((unsigned int)slot >= mInputs.size()) return;
	if(mInputs[slot]){
		mInputs[slot]->removeObserver(this);
	}
	mInputs[slot] = NULL;
	mInputs.erase(mInputs.begin() + slot);
	onAdd(slot);
	return;
}

IAction *BaseAction::getInput(int slot){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if((unsigned int)slot >= mInputs.size()) return NULL;
	return mInputs[slot];
}

unsigned int BaseAction::NumInputs() const{
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

bool BaseAction::checkCycles(IAction *node) const{
	if(!node) return false;
	if(node == this) return true;
	for(unsigned int i = 0; i < node->NumInputs(); i++){
		if(checkCycles(node->getInput(i))){
			return true;
		}
	}
	return false;
}

void BaseAction::notify(const IObservable *origin, NoticeType type, const char *message){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
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
		onNotifyChange(origin, message);
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

void BaseAction::onNotifyChange(const IObservable *origin, const char *message){
	return;
}

void BaseAction::onAdd(unsigned int slot){
	return;
}

void BaseAction::onRemove(unsigned int slot){
	return;
}

} // maudio







