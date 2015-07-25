/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiosink/BaseAudioSink.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

BaseAudioSink::~BaseAudioSink(){
}

AudioBuffer BaseAudioSink::get(unsigned long pos, unsigned int length) noexcept{
	return AudioBuffer();
}

AudioInfo BaseAudioSink::getInfo() noexcept{
	if(checkInput(0)) return getInfoFromSlot(0);
	return AudioInfo();
}

int BaseAudioSink::MaxInputs() const{
	return 1;
}

bool BaseAudioSink::HasOutputs() const{
	return true;
}

bool BaseAudioSink::checkIfCompatible(std::shared_ptr<Node> node, int slot){
	return true;
}

} // maudio




