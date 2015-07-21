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

Sample BaseAudioSink::get(unsigned long pos) noexcept{
	throw BadOutputException();
}

AudioInfo BaseAudioSink::getInfo() noexcept{
	AudioInfo ret;
	if(NumInputs() > 0) return getInfoFromSlot(0);
	return ret;
}

int BaseAudioSink::MaxInputs() const{
	return 1;
}

bool BaseAudioSink::HasOutputs() const{
	return true;
}

} // maudio




