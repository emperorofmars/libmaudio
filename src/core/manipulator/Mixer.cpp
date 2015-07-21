/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/manipulator/Mixer.hpp"
#include <iostream>

namespace maudio{

Mixer::~Mixer(){
}

Sample Mixer::get(unsigned long pos) noexcept{
	Sample ret(getInfo().Channels);
	for(unsigned int i = 0; i < NumInputs(); i++){
		ret += getFromSlot(i, pos);
	}
	for(unsigned int j = 0; j < getInfo().Channels; j++){
		ret.set(j, ret.get(j) / ret.getChannels());
	}
	return ret;
}

AudioInfo Mixer::getInfo() noexcept{
	for(unsigned int i = 0; i < NumInputs(); i++){
		if(checkInput(i)) return getInfoFromSlot(i);
	}
	return AudioInfo();
}

int Mixer::MaxInputs() const{
	return -1;
}

bool Mixer::checkIfCompatible(std::shared_ptr<Node> node, int slot){
	if(!node) return false;
	if(NumInputs() == 0) return true;
	if(getInfo().Channels != node->getInfo().Channels) return false;
	if(getInfo().Samplerate != node->getInfo().Samplerate) return false;
	return true;
}

} // maudio



