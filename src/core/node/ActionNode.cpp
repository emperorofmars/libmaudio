/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/node/ActionNode.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

ActionNode::ActionNode(IAction *action){
}

ActionNode::ActionNode(std::unique_ptr<IAction> action){
}

ActionNode::~ActionNode(){
}

std::shared_ptr<IAudioBuffer> ActionNode::get(unsigned long pos, unsigned int length) noexcept{
	return NULL;
}

std::shared_ptr<IAudioInfo> ActionNode::getInfo() noexcept{
	return NULL;
}

int ActionNode::MaxInputs() const{
	return 0;
}

bool ActionNode::HasOutputs() const{
	return false;
}

void ActionNode::readConfig(const Config &conf){
	return;
}

PropertyManager *ActionNode::getProperties(){
	return NULL;
}

void ActionNode::onAdd(unsigned int slot){
	return;
}

void ActionNode::onRemove(unsigned int slot){
	return;
}


ActionNode::Socket::Socket(std::shared_ptr<Node> input){
}

ActionNode::Socket::~Socket(){
}

IAudioBuffer *ActionNode::Socket::get(unsigned long pos, unsigned int length) noexcept{
	return NULL;
}

IAudioInfo *ActionNode::Socket::getInfo() noexcept{
	return NULL;
}

} // maudio



