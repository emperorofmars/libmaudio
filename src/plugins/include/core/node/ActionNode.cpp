/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/node/ActionNode.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

ActionNode::ActionNode(IAction *action){
	mAction.reset(action);
}

ActionNode::ActionNode(std::unique_ptr<IAction> action){
	mAction = std::move(action);
}

ActionNode::~ActionNode(){
}

IAudioBuffer *ActionNode::get(unsigned long pos, unsigned int length) noexcept{
	if(!mAction) return NULL;
	IAudioBuffer *ret(mAction->get(pos, length));
	return ret;
}

IAudioInfo *ActionNode::getInfo() noexcept{
	if(!mAction) return NULL;
	IAudioInfo *ret(mAction->getInfo());
	return ret;
}

void ActionNode::deleteBuffer(IAudioBuffer *data) noexcept{
	if(mAction) mAction->deleteBuffer(data);
	return;
}

void ActionNode::deleteInfo(IAudioInfo *data) noexcept{
	if(mAction) mAction->deleteInfo(data);
	return;
}

void ActionNode::deleteSample(ISample *data) noexcept{
	if(mAction) mAction->deleteSample(data);
	return;
}

int ActionNode::MaxInputs() const{
	if(!mAction) return 0;
	return mAction->MaxInputs();
}

bool ActionNode::HasOutputs() const{
	if(!mAction) return false;
	return mAction->HasOutputs();
}

void ActionNode::readConfig(const IKeyValueStore &conf){
	if(!mAction) return;
	mAction->readConfig(conf);
	return;
}

IPropertyManager *ActionNode::getProperties(){
	if(!mAction) return NULL;
	return mAction->getProperties();
}

IControl *ActionNode::getControl(){
	if(!mAction) return NULL;
	return mAction->getControl();
}

void ActionNode::onAdd(unsigned int slot){
	if(!mAction) return;
	mAction->addSocket(mInputs[slot].get(), slot);
	return;
}

void ActionNode::onRemove(unsigned int slot){
	if(!mAction) return;
	mAction->removeSocket(slot);
	return;
}

} // maudio



