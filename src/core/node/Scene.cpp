/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/node/Scene.hpp"
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

int Scene::addNode(std::shared_ptr<Node> node){
	if(!node) return -1;
	if(isPartOfScene(node->getID())) return node->getID();
	mEnds.push_back(node);
	notifyObservers(ON_CHANGE, "node added");
	return node->getID();
}

void Scene::removeNode(unsigned int id){
	std::shared_ptr<Node> tmp = getNode(id);
	if(tmp){
		tmp->disconnect();
	}
	notifyObservers(ON_CHANGE, "node removed");
	return;
}

std::shared_ptr<Node> Scene::getEnd(unsigned int num){
	if(num >= mEnds.size()) return NULL;
	return mEnds[num];
}

std::shared_ptr<Node> Scene::getNode(unsigned int id){
	for(unsigned int i = 0; i < mEnds.size(); i++){
		std::shared_ptr<Node> tmp = mEnds[i]->getByID(id);
		if(tmp != NULL){
			return tmp;
		}
	}
	return NULL;
}

void Scene::connect(unsigned int source, unsigned int sink){
	std::shared_ptr<Node> sourceNode = getNode(source);
	std::shared_ptr<Node> sinkNode = getNode(sink);
	if(sourceNode && sinkNode){
		sinkNode->addInput(sourceNode);
	}
	notifyObservers(ON_CHANGE, "node connected");
	return;
}

void Scene::disconnect(unsigned int source, unsigned int sink){
	std::shared_ptr<Node> sourceNode = getNode(source);
	std::shared_ptr<Node> sinkNode = getNode(sink);
	if(sourceNode && sinkNode){
		sinkNode->removeInput(sourceNode);
	}
	notifyObservers(ON_CHANGE, "node disconnected");
	return;
}

bool Scene::isPartOfScene(unsigned int id){
	for(unsigned int i = 0; i < mEnds.size(); i++){
		if(mEnds[i]->getByID(id) != NULL){
			return true;
		}
	}
	return false;
}

} // maudio










