/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiodata/AudioBuffer.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

AudioBuffer::AudioBuffer(AudioInfo info){
	mInfo = info;
	resize(mInfo.Samples);
	return;
}

AudioBuffer::AudioBuffer(unsigned int channels, unsigned long samples, unsigned long offset, unsigned int samplerate){
	mInfo.Channels = channels;
	mInfo.Samples = samples;
	mInfo.Offset = offset;
	mInfo.Samplerate = samplerate;
	resize(mInfo.Samples);
	return;
}

AudioBuffer::~AudioBuffer(){
	return;
}

Sample& AudioBuffer::operator[](unsigned long pos){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw OutOfBoundsException();
	return *createSample(pos);
}

void AudioBuffer::operator=(AudioBuffer &data){
	mInfo = data.getInfo();
	resize(mInfo.Samples);
	for(unsigned int i = 0; i < mInfo.Samples; i++){
		set(i, data[i]);
	}
}

Sample* AudioBuffer::get(unsigned long pos){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw OutOfBoundsException();
	return createSample(pos);
}

void AudioBuffer::set(unsigned long pos, Sample &data){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw OutOfBoundsException();
	if(data.getChannels() != mInfo.Channels) throw ChannelsException();
	for(unsigned int i = 0; i < mInfo.Channels; i++){
		mData[(pos - mInfo.Offset) * mInfo.Channels + i] = data[i];
	}
	return;
}

void AudioBuffer::resize(unsigned long samples){
	mData.resize(samples * mInfo.Channels);
}

void AudioBuffer::setInfo(const AudioInfo &info){
	if(info.Channels != mInfo.Channels) throw ChannelsException();
	mInfo = info;
}

const AudioInfo AudioBuffer::getInfo(){
	return mInfo;
}

Sample* AudioBuffer::createSample(unsigned long pos){
    return new Sample(std::vector<float>(mData.begin() + (pos - mInfo.Offset) * mInfo.Channels, mData.begin() + (pos + 1 - mInfo.Offset) * mInfo.Channels));
}

} // maudio






