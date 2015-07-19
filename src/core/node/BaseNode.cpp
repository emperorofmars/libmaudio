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
	if(node->checkCycles(std::vector<INode*>{this})) throw CircleException();

	if(inputSlot >= (int)mInputs.size()) mInputs.resize(inputSlot);

	try{
		if(inputSlot < 0){
			mInputs.push_back(node->getEdge(shared_from_this()));
		}
		else{
			mInputs[inputSlot] = node->getEdge(shared_from_this());
		}
	}
	catch(std::exception &e){
	}
	catch(...){
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

std::shared_ptr<INode> BaseNode::getByID(unsigned int id){
	if(getID() == id) return shared_from_this();
	std::shared_ptr<INode> ret;
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i]){
			ret = mInputs[i]->getInput()->getByID(id);
			if(ret && ret->getID() == id) return ret;
		}
	}
	return NULL;
}

std::vector<std::shared_ptr<INode>> BaseNode::getOutputs(){
	std::vector<std::shared_ptr<INode>> ret;
	for(unsigned int i = 0; i < mOutputs.size(); i++){
		std::shared_ptr<Edge> tmp = mOutputs[i].lock();
		if(tmp && tmp->valid()) ret.push_back(tmp->getOutput());
	}
	return ret;
}

void BaseNode::disconnect(){
	mInputs.clear();

	for(unsigned int i = 0; i < mOutputs.size(); i++){
		std::shared_ptr<Edge> tmp = mOutputs[i].lock();
		if(tmp && tmp->valid()) tmp->expire();
	}
	mOutputs.clear();
	return;
}

int BaseNode::getNumInputs(){
	return mInputs.size();
}

std::shared_ptr<Edge> BaseNode::getEdge(std::weak_ptr<INode> output){
	return std::shared_ptr<Edge>(new Edge(shared_from_this(), output));
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

} // maudio



