/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/util/AudioBuffer.hpp"
#include "core/util/AudioException.hpp"
#include "core/util/Sample.hpp"

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

ISample& AudioBuffer::operator[](unsigned long pos){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw OutOfBoundsException();
	return *mData[pos - mInfo.Offset];
}

void AudioBuffer::operator=(IAudioBuffer &data){
	mData.resize(data.getInfo().Samples, new Sample(data.getInfo().Channels));
	for(unsigned int i = 0; i < data.getInfo().Samples; i++){
		*(mData[i]) = data[i];
	}
}

ISample& AudioBuffer::get(unsigned long pos){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw OutOfBoundsException();
	return *mData[pos - mInfo.Offset];
}

void AudioBuffer::set(ISample &data, unsigned long pos){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw ChannelsException();
	*(mData[pos - mInfo.Offset]) = data;
	return;
}

void AudioBuffer::resize(unsigned long samples){
	mData.resize(samples, new Sample(mInfo.Channels));
}

void AudioBuffer::setInfo(const AudioInfo &info){
	if(info.Channels != mInfo.Channels) throw ChannelsException();
	mInfo = info;
}

const AudioInfo AudioBuffer::getInfo(){
	return mInfo;
}

} // maudio






