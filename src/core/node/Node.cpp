/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/node/Node.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

Node::~Node(){
}

void Node::addInput(std::shared_ptr<Node> node, int slot){
	if(!node) throw MaudioException("passed invalid node");
	if(!node->HasOutputs()) throw MaudioException("node has no outputs");
	if(MaxInputs() >= 0 && slot >= MaxInputs()) throw MaudioException("invalid input slot");
	if(!checkIfCompatible(node)) throw MaudioException("input is not compatible");
	if(checkCycles(node)){
		throw MaudioException("adding this would create a cycle");
	}

	if(slot < 0){
		mInputs.push_back(node);
	}
	else if((unsigned int)slot >= mInputs.size()){
		mInputs.resize(slot + 1);
		mInputs[slot] = node;
	}
	else{
		mInputs[slot] = node;
	}
	node->mOutputs.push_back(shared_from_this());
	return;
}

void Node::removeInput(std::shared_ptr<Node> node){
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i] == node){
			removeInput(i);
		}
	}
	return;
}

void Node::removeInput(int slot){
	if((unsigned int)slot < mInputs.size()){
		for(unsigned int i = 0; i < mInputs[slot]->mOutputs.size(); i++){
			if(mInputs[slot]->mOutputs[i].lock().get() == this){
				mInputs[slot]->mOutputs.erase(mInputs[slot]->mOutputs.begin() + i);
				i--;
			}
		}
		mInputs.erase(mInputs.begin() + slot);
	}
	return;
}

std::shared_ptr<Node> Node::getInput(int slot){
	if((unsigned int)slot < mInputs.size()){
		return mInputs[slot];
	}
	return NULL;
}

std::shared_ptr<Node> Node::getOutput(int slot){
	if((unsigned int)slot < mOutputs.size()){
		return mOutputs[slot].lock();
	}
	return NULL;
}

std::shared_ptr<Node> Node::getByID(unsigned int id){
	if(id == getID()) return shared_from_this();
	for(unsigned int i = 0; i < mInputs.size(); i++){
		std::shared_ptr<Node> tmp = mInputs[i]->getByID(id);
		if(tmp) return tmp;
	}
	return NULL;
}

void Node::disconnect(){
	for(unsigned int i = 0; i < mOutputs.size(); i++){
		mOutputs[i].lock()->removeInput(shared_from_this());
	}
	mOutputs.clear();
	mInputs.clear();
	return;
}

unsigned int Node::NumInputs() const{
	return mInputs.size();
}

unsigned int Node::NumOutputs() const{
	return mOutputs.size();
}

bool Node::checkInput(unsigned int slot) noexcept{
	if(slot < mInputs.size() && mInputs[slot]) return true;
	return false;
}

AudioBuffer Node::getFromSlot(unsigned long pos, unsigned int length, unsigned int slot) noexcept{
	if(slot < mInputs.size() && mInputs[slot]){
		return mInputs[slot]->get(pos, length);
	}
	return AudioBuffer(getInfo().Channels);
}

AudioInfo Node::getInfoFromSlot(unsigned int slot) noexcept{
	if(slot < mInputs.size() && mInputs[slot]){
		return mInputs[slot]->getInfo();
	}
	return AudioInfo();
}

bool Node::checkCycles(std::shared_ptr<Node> node){
	if(node.get() == this) return true;
	return node->checkCyclesDeep(std::vector<std::shared_ptr<Node>>{shared_from_this()});
}

bool Node::checkCyclesDeep(std::vector<std::shared_ptr<Node>> nodes){
	for(unsigned int i = 0; i < nodes.size(); i++){
		if(nodes[i].get() == this) return true;
	}
	nodes.push_back(shared_from_this());
	for(unsigned int i = 0; i < mInputs.size(); i++){
		if(mInputs[i] && mInputs[i]->checkCyclesDeep(nodes)) return true;
	}
	return false;
}

} // maudio



