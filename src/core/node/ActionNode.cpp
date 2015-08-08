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
	return mInput->get(pos, length);
}

IAudioInfo *ActionNode::Socket::getInfo() noexcept{
	if(!mInput) return NULL;
	return mInput->getInfo();
}

IKeyValueStore *ActionNode::serialize() const{
	return NULL;
}

void ActionNode::deserialize(const IKeyValueStore *data){
	return;
}

} // maudio



