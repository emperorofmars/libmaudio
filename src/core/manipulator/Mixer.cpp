/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/manipulator/Mixer.hpp"

namespace maudio{

Mixer::Mixer(){
}

Mixer::~Mixer(){
}

AudioBuffer Mixer::get(unsigned long pos, unsigned int length) noexcept{
	AudioBuffer ret(getInfo().Channels, length, pos, getInfo().Samplerate);
	if(NumInputs() > 0){
		for(unsigned int i = 0; i < NumInputs(); i++){
			AudioBuffer tmp = getFromSlot(pos, length, i);
			for(unsigned int j = 0; j < length; j++){
				ret.set(j, ret.get(j) + tmp.get(j));
			}
		}
		for(unsigned int j = 0; j < length; j++){
			ret.set(j, ret.get(j) / NumInputs());
		}
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

void Mixer::readConfig(const Config &conf){
    return;
}

} // maudio



