/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
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

void BaseAudioSource::onAdd(unsigned int slot){
	return;
}

void BaseAudioSource::onRemove(unsigned int slot){
	return;
}

} // maudio




