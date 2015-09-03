/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/action/SinusGenerator.hpp"
#include "core/audiodata/AudioBuffer.hpp"
#include "core/util/AudioException.hpp"
#include "core/util/Util.hpp"
#include <cmath>
#include <iostream>

namespace maudio{

SinusGenerator::SinusGenerator(){
	mFreq.reset(new KeyableFloatProperty("Frequency", 1000));
	mProperties.add(mFreq.get());
	mSamplerate.reset(new UIntProperty("Samplerate", 44100));
	mProperties.add(mSamplerate.get());
	mChannels.reset(new UIntProperty("Channels", 1));
	mProperties.add(mChannels.get());

	mAudioInfo.setChannels(mChannels->get());
	mAudioInfo.setOffset(0);
	mAudioInfo.setSamplerate(mSamplerate->get());
	mAudioInfo.setSamples(-1);
}

SinusGenerator::~SinusGenerator(){
}

IAudioBuffer *SinusGenerator::get(unsigned long pos, unsigned int length) noexcept{
	mAudioInfo.setChannels(mChannels->get());
	mAudioInfo.setSamplerate(mSamplerate->get());
	AudioBuffer *ret = new AudioBuffer(mAudioInfo.getChannels(), length, pos, mAudioInfo.getSamplerate());

	for(unsigned int i = 0; i < length; i++){
		Sample tmp(mAudioInfo.getChannels());
		//std::cerr << pos + i << " " << mFreq->get(PositionToSeconds(pos + i, mAudioInfo.getSamplerate())) << std::endl;
		double value = sin(mFreq->get(PositionToSeconds(pos + i, mAudioInfo.getSamplerate()))
					//* ((pos + i) % mAudioInfo.getSamplerate())
					* (pos + i)
					* (2 * M_PI) / mAudioInfo.getSamplerate());
		for(unsigned int j = 0; j < mAudioInfo.getChannels(); j++){
            tmp.set(value, j);
		}
		ret->set(tmp, i);
	}
	return ret;
}

IAudioInfo *SinusGenerator::getInfo() noexcept{
	mAudioInfo.setChannels(mChannels->get());
	mAudioInfo.setSamplerate(mSamplerate->get());
	AudioInfo *ret = new AudioInfo();
	*ret = mAudioInfo;
	return ret;
}

int SinusGenerator::MaxInputs() const{
	return 0;
}

bool SinusGenerator::HasOutputs() const{
	return true;
}

void SinusGenerator::readConfig(const IKeyValueStore &conf){
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

void SinusGenerator::serialize(IMultiLevelStore *data) const{
	if(!data) return;
	data->add("type", "SinusGenerator");
	data->add("name", mName.c_str());
	mFreq->serialize(data->addLevel("Frequency"));
	mSamplerate->serialize(data->addLevel("Samplerate"));
	mChannels->serialize(data->addLevel("Channels"));
	return;
}

void SinusGenerator::deserialize(const IMultiLevelStore *data){
	if(!data) return;
	try{
		mName = data->get("name");
		
		mFreq->deserialize(data->getLevel("Frequency"));
		mSamplerate->deserialize(data->getLevel("Samplerate"));
		mChannels->deserialize(data->getLevel("Channels"));

		mAudioInfo.setChannels(mChannels->get());
		mAudioInfo.setOffset(0);
		mAudioInfo.setSamplerate(mSamplerate->get());
		mAudioInfo.setSamples(-1);
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

} // maudio



