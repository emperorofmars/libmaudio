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

Sample Resampler::get(unsigned long pos) noexcept{
	Sample ret(getInfo().Channels);
	if(NumInputs() > 0){
		unsigned int imputSamplerate = getInfoFromSlot(0).Samplerate;
		unsigned long realPos = (double)pos * ((double)imputSamplerate / (double)mOutputSamplerate);
		ret = getFromSlot(realPos, 0);
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

void Resampler::setSampleRate(unsigned int samplerate){
	mOutputSamplerate = samplerate;
}

unsigned int Resampler::getSampleRate(){
	return mOutputSamplerate;
}

} // maudio



