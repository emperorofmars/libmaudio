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

AudioBuffer::AudioBuffer(const AudioBuffer &data){
	*this = data;
	return;
}

AudioBuffer::~AudioBuffer(){
	return;
}

Sample AudioBuffer::operator[](unsigned long pos) const{
	return createSample(pos);
}

void AudioBuffer::operator=(const AudioBuffer &data){
	mInfo = data.getInfo();
	mData = data.mData;
}

Sample AudioBuffer::get(unsigned long pos) const{
	return createSample(pos);
}

void AudioBuffer::set(const Sample &data, unsigned long pos){
	if(pos >= mData.size()) return;
	if(data.getChannels() != mInfo.Channels) return;
	for(unsigned int i = 0; i < mInfo.Channels; i++){
		mData[pos * mInfo.Channels + i] = data.get(i);
	}
	return;
}

void AudioBuffer::resize(unsigned long samples){
	mData.resize(samples * mInfo.Channels);
}

AudioInfo AudioBuffer::getInfo() const{
	return mInfo;
}

Sample AudioBuffer::createSample(unsigned long pos) const{
	if(pos >= mData.size()) return Sample(mInfo.Channels);
    return Sample(std::vector<float>(mData.begin() + (pos) * mInfo.Channels, mData.begin() + (pos + 1) * mInfo.Channels));
}

} // maudio






