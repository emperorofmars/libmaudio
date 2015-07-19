/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/node/BaseNode.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

BaseNode::~BaseNode(){
}

void BaseNode::addInput(std::shared_ptr<INode> node, int inputSlot){
	if(inputSlot >= getMaxInputs()) throw BadInputException();
	if(checkCycles(std::vector<INode*>{node.get()})) throw CircleException();

	if(inputSlot >= (int)mInputs.size()) mInputs.resize(inputSlot);

	if(inputSlot < 0){
		mInputs.push_back(node->getLink(shared_from_this()));
	}
	else{
		mInputs[inputSlot] = node->getLink(shared_from_this());
	}
	return;
}

void BaseNode::removeInput(std::shared_ptr<INode> node){
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i] && mInputs[i]->getInput() == node) mInputs.erase(mInputs.begin() + i);
	}
	return;
}

void BaseNode::removeInput(int inputSlot){
	if(inputSlot >= (int)mInputs.size() || !mInputs[inputSlot]) throw BadInputException();
	mInputs.erase(mInputs.begin() + inputSlot);
	return;
}

std::shared_ptr<INode> BaseNode::getInput(int inputSlot){
	if(inputSlot >= (int)mInputs.size() || !mInputs[inputSlot]) throw BadInputException();
	return mInputs[inputSlot]->getInput();
}

std::vector<std::shared_ptr<INode>> BaseNode::getOutputs(){
	std::vector<std::shared_ptr<INode>> ret;
	for(unsigned int i = 0; i < mOutputs.size(); i++){
		std::shared_ptr<ILink> tmp = mOutputs[i].lock();
		if(tmp && tmp->valid()) ret.push_back(tmp->getOutput());
	}
	return ret;
}

void BaseNode::disconnect(){
	mInputs.clear();

	for(unsigned int i = 0; i < mOutputs.size(); i++){
		std::shared_ptr<ILink> tmp = mOutputs[i].lock();
		if(tmp && tmp->valid()) tmp->expire();
	}
	mOutputs.clear();
	return;
}

bool BaseNode::checkCycles(std::vector<INode*> elements){
	for(unsigned int i; i < elements.size(); i++){
		if(elements[i] == this) return true;
	}
	elements.push_back(this);
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i] && mInputs[i]->getInput() && mInputs[i]->getInput()->checkCycles(elements)) return true;
	}
	return false;
}


BaseNode::BaseLink::~BaseLink(){
}

bool BaseNode::BaseLink::valid(){
	if(mInput || !mOutput.expired()) return true;
	return false;
}

void BaseNode::BaseLink::expire(){
	mInput.reset();
	mOutput.reset();
}

std::shared_ptr<INode> BaseNode::BaseLink::getInput(){
	return mInput;
}

std::shared_ptr<INode> BaseNode::BaseLink::getOutput(){
	return mOutput.lock();
}

void BaseNode::BaseLink::setInput(std::shared_ptr<INode> node){
	mInput = node;
	return;
}

void BaseNode::BaseLink::setOutput(std::weak_ptr<INode> node){
	mOutput = node;
	return;
}

} // maudio



