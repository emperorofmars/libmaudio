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

Sample BaseAudioSink::get(unsigned long pos){
	throw BadOutputException();
}

AudioInfo BaseAudioSink::getAudioInfo(){
	AudioInfo ret;
	if(mInputs.size() > 0 && mInputs[0] && mInputs[0]->valid()) ret = mInputs[0]->getInput()->getAudioInfo();
	return ret;
}

int BaseAudioSink::getMaxInputs(){
	return 1;
}

bool BaseAudioSink::HasOutputs(){
	return true;
}

std::shared_ptr<Edge> BaseAudioSink::getEdge(std::weak_ptr<INode> output){
	throw BadOutputException();
}

} // maudio




