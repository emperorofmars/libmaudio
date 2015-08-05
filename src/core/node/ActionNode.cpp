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

std::shared_ptr<IAudioBuffer> ActionNode::get(unsigned long pos, unsigned int length) noexcept{
	if(!mAction) return NULL;
	std::shared_ptr<IAudioBuffer> ret(mAction->get(pos, length));
	return ret;
}

std::shared_ptr<IAudioInfo> ActionNode::getInfo() noexcept{
	if(!mAction) return NULL;
	std::shared_ptr<IAudioInfo> ret(mAction->getInfo());
	return ret;
}

int ActionNode::MaxInputs() const{
	if(!mAction) return 0;
	return mAction->MaxInputs();
}

bool ActionNode::HasOutputs() const{
	if(!mAction) return false;
	return mAction->HasOutputs();
}

void ActionNode::readConfig(const Config &conf){
	if(!mAction) return;
	mAction->readConfig(conf);
	return;
}

PropertyManager *ActionNode::getProperties(){
	if(!mAction) return NULL;
	return mAction->getProperties();
}

void ActionNode::onAdd(unsigned int slot){
	if(!mAction) return;
	mAction->addSocket(new Socket(mInputs[slot]), slot);
	return;
}

void ActionNode::onRemove(unsigned int slot){
	if(!mAction) return;
	mAction->removeSocket(slot);
	return;
}


ActionNode::Socket::Socket(std::shared_ptr<Node> input){
	mInput = input;
}

ActionNode::Socket::~Socket(){
}

IAudioBuffer *ActionNode::Socket::get(unsigned long pos, unsigned int length) noexcept{
	if(!mInput) return NULL;
	return mInput->get(pos, length).get();
}

IAudioInfo *ActionNode::Socket::getInfo() noexcept{
	if(!mInput) return NULL;
	return mInput->getInfo().get();
}

} // maudio



