/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiosource/SinusGenerator.hpp"
#include "core/util/AudioException.hpp"
#include "core/util/Util.hpp"
#include <cmath>

namespace maudio{

SinusGenerator::SinusGenerator(){
	mAudioInfo.mFileInfo.Title = "Sinus Test Generator from Maudio";

	mFreq.reset(new KeyableFloatProperty("Frequency", 1000));
	mProperties.add(mFreq);
	mSamplerate.reset(new UIntProperty("Samplerate", 44100));
	mProperties.add(mSamplerate);
	mChannels.reset(new UIntProperty("Channels", 1));
	mProperties.add(mChannels);

	mAudioInfo.Channels = mChannels->get();
	mAudioInfo.Offset = 0;
	mAudioInfo.Samplerate = mSamplerate->get();
	mAudioInfo.Samples = -1;
}

SinusGenerator::~SinusGenerator(){
}

AudioBuffer SinusGenerator::get(unsigned long pos, unsigned int length) noexcept{
	mAudioInfo.Channels = mChannels->get();
	mAudioInfo.Samplerate = mSamplerate->get();
	AudioBuffer ret(mAudioInfo.Channels, length, pos, mAudioInfo.Samplerate);
	for(unsigned int i = 0; i < length; i++){
		Sample tmp(mAudioInfo.Channels);
		float index = pos + i;
		for(unsigned int j = 0; j < mAudioInfo.Channels; j++){
            tmp.set(sin(mFreq->get(PositionToSeconds((pos + i), mAudioInfo.Samplerate))
						* index * (2 * M_PI) / mAudioInfo.Samplerate), j);
		}
		ret.set(tmp, i);
	}
	return ret;
}

AudioInfo SinusGenerator::getInfo() noexcept{
	mAudioInfo.Channels = mChannels->get();
	mAudioInfo.Samplerate = mSamplerate->get();
	return mAudioInfo;
}

bool SinusGenerator::checkIfCompatible(std::shared_ptr<Node> node, int slot){
	return true;
}

void SinusGenerator::readConfig(const Config &conf){
    return;
}

void SinusGenerator::setFrequency(float freq){
	mFreq->setKey(freq, 0);
}

void SinusGenerator::setSamplerate(unsigned int samplerate){
	mSamplerate->set(samplerate);
}

void SinusGenerator::setChannels(unsigned int channels){
	mChannels->set(channels);
}

} // maudio



