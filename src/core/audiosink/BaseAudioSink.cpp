/*
 * INode specialisation for AudioSinks
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiosink/BaseAudioSink.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

BaseAudioSink::~BaseAudioSink(){
}

Sample BaseAudioSink::get(unsigned long pos, int output){
	throw BadInputException();
}

void BaseAudioSink::addNode(std::shared_ptr<INode> node, int inputPos){
	if(inputPos > 0) throw BadOutputException();
	mNodes.resize(1);
	mNodes[0] = node;
	return;
}

void BaseAudioSink::removeNode(std::shared_ptr<INode> node){
	if(mNodes.size() > 0 && mNodes[0] == node) mNodes[0].reset();
	return;
}

void BaseAudioSink::removeNode(int inputPos){
	if(inputPos == 0 && mNodes.size() > 0) mNodes[0].reset();
	return;
}

std::vector<std::shared_ptr<INode>> BaseAudioSink::getNodes(){
	return mNodes;
}

int BaseAudioSink::getMaxInput(){
	return 1;
}

} // maudio




