/*
 * INode specialisation for AudioSource
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiosource/BaseAudioSource.hpp"

namespace maudio{

BaseAudioSource::~BaseAudioSource(){
}

int BaseAudioSource::MaxInputs() const{
	return 0;
}

bool BaseAudioSource::HasOutputs() const{
	return true;
}

} // maudio




