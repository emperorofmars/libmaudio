/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/scene/Scene.hpp"
#include "core/scene/TypeManager.hpp"
#include "core/util/Util.hpp"
#include "core/util/AudioException.hpp"
#include <sstream>

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

const char *Scene::getName() const{
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
	for(auto iter1 = mAdjacencyList.begin(); iter1 != mAdjacencyList.end(); iter1 ++){
		unsigned long tmp = iter1->first;
		bool isEnd = true;
		for(auto iter2 = mAdjacencyList.begin(); iter2 != mAdjacencyList.end(); iter2 ++){
			for(unsigned int i = 0; i < iter2->second.size(); i++){
				if(tmp == iter2->first) continue;
				if(tmp == iter2->second[i]){
					isEnd = false;
					break;
				}
			}
			if(!isEnd) break;
		}
		if(isEnd){
			if(num == 0) return mNodes[tmp];
			num--;
		}
	}
	return NULL;
}

sptr<IAction> Scene::get(unsigned long id){
	return mNodes[id];
}

unsigned int Scene::getNumEnds(){
	unsigned int ret = 0;
	for(auto iter1 = mAdjacencyList.begin(); iter1 != mAdjacencyList.end(); iter1 ++){
		unsigned long tmp = iter1->first;
		bool isEnd = true;
		for(auto iter2 = mAdjacencyList.begin(); iter2 != mAdjacencyList.end(); iter2 ++){
			for(unsigned int i = 0; i < iter2->second.size(); i++){
				if(tmp == iter2->first) continue;
				if(tmp == iter2->second[i]){
					isEnd = false;
					break;
				}
			}
			if(!isEnd) break;
		}
		if(isEnd){
			ret++;
		}
	}
	return ret;
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

void Scene::readConfig(const IKeyValueStore *conf){
	if(!conf) return;
	for(auto iter = mNodes.begin(); iter != mNodes.end(); iter++){
		if(iter->second) iter->second->readConfig(conf);
	}
	return;
}

void Scene::serialize(IMultiLevelStore *data) const{
	if(!data) return;
	data->add("name", mName.c_str());
	for(auto iter = mNodes.begin(); iter != mNodes.end(); iter++){
		if(iter->second){
			IMultiLevelStore *nodeStore = data->addLevel("node");
			iter->second->serialize(nodeStore->addLevel("node"));
			nodeStore->add("type", iter->second.getType());
			nodeStore->add("id", std::to_string(iter->second->getID()).c_str());
		}
	}
	IMultiLevelStore *adjacencyStore = data->addLevel("adjacencylist");
	for(auto iter = mAdjacencyList.begin(); iter != mAdjacencyList.end(); iter++){
		if(iter->second.size() > 0){
			std::string value;
			value.append(std::to_string(iter->first)).append(" ");
			
			for(unsigned int i = 0; i < iter->second.size(); i++){
				value.append(std::to_string(iter->second[i])).append(" ");
			}
			adjacencyStore->add("inputs", value.c_str());
		}
	}
	return;
}

void Scene::deserialize(const IMultiLevelStore *data){
	if(!data) return;
	try{
		mName = data->get("name");
		
		std::map<unsigned long, unsigned long> idConversion;
		
		for(unsigned int i = 0; i < data->getNumLevels("node"); i++){
			IMultiLevelStore *nodeStore = data->getLevel("node", i);
			IMultiLevelStore *innerNodeStore = nodeStore->getLevel("node");
			try{
				std::string type = nodeStore->get("type");
				sptr<IAction> action = TypeManager::create(type.c_str());
				if(!action) continue; //TODO: replace with invalid
				action->deserialize(innerNodeStore);
				idConversion[string_to<unsigned long>(std::string(nodeStore->get("id")))] = action->getID();
				add(action);
			}
			catch(std::exception &e){
				//
			}
		}
		IMultiLevelStore *adjacencyStore = data->getLevel("adjacencylist");
		for(unsigned int i = 0; i < adjacencyStore->getSize("inputs"); i++){
			try{
				std::string strValues = adjacencyStore->get("inputs", i);
				std::stringstream ss(strValues);
				unsigned int key = 0;
				ss >> key;
				std::vector<unsigned long> numValues;
				unsigned int tmp = 0;
				while(ss >> tmp){
					numValues.push_back(idConversion[tmp]);
				}
				mAdjacencyList[idConversion[key]] = numValues;
			}
			catch(std::exception &e){
				//
			}
		}
		for(auto iter = mAdjacencyList.begin(); iter != mAdjacencyList.end(); iter++){
			for(unsigned int i = 0; i < iter->second.size(); i++){
				if(!mNodes[iter->first] || !mNodes[iter->second[i]]){
					continue;
				}
				mNodes[iter->first]->addInput(mNodes[iter->second[i]].get(), -1);
			}
		}
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

bool Scene::isPartOfScene(unsigned long id){
	if(mNodes[id]) return true;
	return false;
}

} // maudio










