/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiosource/SinusGenerator.hpp"
#include "core/util/AudioException.hpp"
#include <cmath>

namespace maudio{

SinusGenerator::SinusGenerator(){
	mAudioInfo.mFileInfo.Title = "Sinus Test Generator from Maudio";

	mFreq = 1000;

	mAudioInfo.Channels = 1;
	mAudioInfo.Offset = 0;
	mAudioInfo.Samplerate = 44100;
	mAudioInfo.Samples = -1;
}

SinusGenerator::~SinusGenerator(){
}

AudioBuffer SinusGenerator::get(unsigned long pos, unsigned int length) noexcept{
	AudioBuffer ret(mAudioInfo.Channels, length, pos, mAudioInfo.Samplerate);
	for(unsigned int i = 0; i < length; i++){
		Sample tmp(mAudioInfo.Channels);
		float index = pos + i;
		for(unsigned int j = 0; j < mAudioInfo.Channels; j++){
            tmp.set(sin(mFreq * index * (2 * M_PI) / mAudioInfo.Samplerate), j);
		}
		ret.set(tmp, i);
	}
	return ret;
}

bool SinusGenerator::checkIfCompatible(std::shared_ptr<Node> node, int slot){
	return true;
}

void SinusGenerator::readConfig(const Config &conf){
    return;
}

AudioInfo SinusGenerator::getInfo() noexcept{
	return mAudioInfo;
}

void SinusGenerator::setFrequency(float freq){
	mFreq = freq;
}

void SinusGenerator::setSamplerate(unsigned int samplerate){
	mAudioInfo.Samplerate = samplerate;
}

void SinusGenerator::setChannels(unsigned int channels){
	mAudioInfo.Channels = channels;
}

} // maudio



