/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/node/BaseNode.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

BaseNode::~BaseNode(){
}

void BaseNode::addNode(std::shared_ptr<INode> node, int inputPos){
	return;
}

void BaseNode::removeNode(std::shared_ptr<INode> node){
	return;
}

void BaseNode::removeNode(int inputPos){
	return;
}

std::vector<std::shared_ptr<INode>> BaseNode::getNodes(){
	return mNodes;
}

} // maudio



