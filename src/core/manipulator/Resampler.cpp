/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/manipulator/Resampler.hpp"

namespace maudio{

Resampler::Resampler(unsigned int samplerate){
	mOutputSamplerate = samplerate;
}

Resampler::~Resampler(){
}

AudioBuffer Resampler::get(unsigned long pos, unsigned int length) noexcept{
	AudioBuffer ret(getInfo().Channels, length, pos, getInfo().Samplerate);
	if(NumInputs() > 0){
		unsigned int imputSamplerate = getInfoFromSlot(0).Samplerate;
		double multiplier = (double)imputSamplerate / (double)mOutputSamplerate;
		AudioBuffer tmp = getFromSlot(pos * multiplier, length * multiplier + 1, 0);

		for(unsigned int i = 0; i < length; i++){
            ret.set(i, tmp.get(i * multiplier));
		}
	}
	return ret;
}

AudioInfo Resampler::getInfo() noexcept{
	AudioInfo ret;
	if(checkInput(0)) ret = getInfoFromSlot(0);
	ret.Samplerate = mOutputSamplerate;
	return ret;
}

int Resampler::MaxInputs() const{
	return 1;
}

bool Resampler::checkIfCompatible(std::shared_ptr<Node> node, int slot){
	return true;
}

void Resampler::readConfig(const Config &conf){
    return;
}

void Resampler::setSampleRate(unsigned int samplerate){
	mOutputSamplerate = samplerate;
}

unsigned int Resampler::getSampleRate(){
	return mOutputSamplerate;
}

} // maudio



