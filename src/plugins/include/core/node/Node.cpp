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
	if(checkCycles(node)) throw MaudioException("adding this would create a cycle");

	if(slot < 0){
		mInputs.push_back(node);
	}
	else{
		if((unsigned int)slot >= mInputs.size()){
			mInputs.resize(slot + 1);
		}
		mInputs[slot] = node;
	}
	node->addOutput(shared_from_this());

	onAdd(slot);
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
		mInputs[slot]->removeOutput(shared_from_this());
		mInputs[slot].reset();
	}
	onRemove(slot);
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
		i--;
	}
	for(unsigned int i = 0; i < mInputs.size(); i++){
		removeInput(i);
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

std::string Node::getName() const{
	return mName;
}

void Node::setName(const std::string &name){
	mName = name;
	return;
}

void Node::addOutput(std::weak_ptr<Node> node){
	mOutputs.push_back(node);
	return;
}

void Node::removeOutput(std::weak_ptr<Node> node){
	for(unsigned int i = 0; i < mOutputs.size(); i++){
		if(mOutputs[i].lock().get() == node.lock().get()){
			mOutputs.erase(mOutputs.begin() + i);
			i--;
			break;
		}
	}
	return;
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



