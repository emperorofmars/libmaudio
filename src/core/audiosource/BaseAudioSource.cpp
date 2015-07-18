/*
 * INode specialisation for AudioSource
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiosource/BaseAudioSource.hpp"

namespace maudio{

BaseAudioSource::~BaseAudioSource(){
}

int BaseAudioSource::getMaxInput(){
	return 0;
}

} // maudio




