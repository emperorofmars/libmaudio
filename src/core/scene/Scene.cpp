/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/scene/Scene.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

Scene::Scene(const char *name){
	setName(name);
}

Scene::~Scene(){
}

void Scene::setName(const char *name){
	mName = name;
	return;
}

const char *Scene::getName(){
	return mName.c_str();
}

long Scene::add(IAction *node){
	return add(sptr<IAction>(node));
}

long Scene::add(sptr<IAction> node){
	if(!node) return -1;
	if(isPartOfScene(node->getID())) return node->getID();
	mNodes[node->getID()] = node;
	mAdjacencyList[node->getID()] = std::vector<unsigned long>();
	notifyObservers(ON_CHANGE, "node added");
	return node->getID();
}

void Scene::remove(unsigned long id){
	if(!isPartOfScene(id)) return;
	std::vector<unsigned long> outputs = getOutputs(id);
	for(unsigned int i = 0; i < outputs.size(); i++){
		disconnect(id, outputs[i]);
	}
	for(unsigned int i = 0; i < mNodes[id]->NumInputs(); i++){
		disconnect(mNodes[id]->getInput(i)->getID(), id);
	}
	mNodes[id].reset();
	mAdjacencyList[id].clear();
	notifyObservers(ON_CHANGE, "node removed");
	return;
}

sptr<IAction> Scene::getEnd(unsigned int num){
	if(num >= mAdjacencyList.size()) return NULL;
	for(auto iter = mAdjacencyList.begin(); iter != mAdjacencyList.end(); iter ++){
		if(iter->second.size() == 0 && mNodes[iter->first] > 0 && num == 0) return mNodes[iter->first];
		if(num == 0) return NULL;
	}
	return NULL;
}

sptr<IAction> Scene::get(unsigned long id){
	return mNodes[id];
}

void Scene::connect(unsigned long source, unsigned long sink){
	sptr<IAction> sourceNode = get(source);
	sptr<IAction> sinkNode = get(sink);
	if(sourceNode && sinkNode){
		if(!sinkNode->addInput(sourceNode.get(), -1)){
			throw MaudioException("cant connect");
		}
		mAdjacencyList[sink].push_back(source);
	}
	notifyObservers(ON_CHANGE, "node connected");
	return;
}

void Scene::disconnect(unsigned long source, unsigned long sink){
	sptr<IAction> sourceNode = get(source);
	sptr<IAction> sinkNode = get(sink);
	if(sourceNode && sinkNode){
		sinkNode->removeInput(sourceNode.get());
		for(unsigned int i = 0; i < mAdjacencyList[sink].size(); i++){
			if(mAdjacencyList[sink][i] == source){
				mAdjacencyList[sink].erase(mAdjacencyList[sink].begin() + i);
			}
		}
	}
	notifyObservers(ON_CHANGE, "node disconnected");
	return;
}

std::vector<unsigned long> Scene::getOutputs(unsigned long id){
	std::vector<unsigned long> ret;
	for(auto iter = mAdjacencyList.begin(); iter != mAdjacencyList.end(); iter++){
		if(iter->first && iter->second.size() > 0){
			for(unsigned int i = 0; i < iter->second.size(); i++){
				if(iter->second[i] == id) ret.push_back(iter->first);
			}
		}
	}
	return ret;
}
void Scene::serialize(IMultiLevelStore *data) const{
	return;
}

void Scene::deserialize(const IMultiLevelStore *data){
	return;
}

bool Scene::isPartOfScene(unsigned long id){
	if(mNodes[id]) return true;
	return false;
}

} // maudio










