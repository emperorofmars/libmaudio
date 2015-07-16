/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include <iostream>
#include "core/util/AudioBuffer.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

AudioBuffer::AudioBuffer(AudioInfo info){
	mInfo = info;
	setLength();
	return;
}

AudioBuffer::AudioBuffer(unsigned long samples, unsigned int channels){
	mInfo.Samples = samples;
	mInfo.Channels = channels;
	setLength();
	return;
}

AudioBuffer::~AudioBuffer(){
	return;
}

void AudioBuffer::setLength(){
	mData.resize(mInfo.Samples * mInfo.Channels);
	return;
}

std::vector<float> AudioBuffer::get(){
	return mData;
}

Sample AudioBuffer::get(unsigned long sample){
	if((sample + 1) * mInfo.Channels >= mData.size()) throw OutOfBoundsException();
	std::vector<float> data;
	for(unsigned int i = sample * mInfo.Channels; i < (sample + 1) * mInfo.Channels; i++){
		data.push_back(mData[i]);
	}
	return Sample(data);
}

Sample AudioBuffer::operator[](unsigned long sample){
	if((sample + 1) * mInfo.Channels >= mData.size()) throw OutOfBoundsException();
	//if((sample + 1) * mInfo.Channels >= mData.size()) return Sample(std::vector<float> (0, mInfo.Channels));
	std::vector<float> data;
	for(unsigned int i = sample * mInfo.Channels; i < (sample + 1) * mInfo.Channels; i++){
		data.push_back(mData[i]);
	}
	return Sample(data);
}

void AudioBuffer::set(unsigned long sample, Sample data){
	if((sample + 1) * mInfo.Channels >= mData.size()) throw OutOfBoundsException();
	if(data.getChannels() != mInfo.Channels) throw ChannelsException();
	for(unsigned int i = 0; i < mInfo.Channels; i++){
		mData[sample * mInfo.Channels + i] = data[i];
	}
	return;
}

void AudioBuffer::setInfo(AudioInfo info){
	if(info.Channels != mInfo.Channels) throw ChannelsException();
	mInfo = info;
	setLength();
	return;
}

AudioInfo AudioBuffer::getInfo(){
	return mInfo;
}

} // maudio






