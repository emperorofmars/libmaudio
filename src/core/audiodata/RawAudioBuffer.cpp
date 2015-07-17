/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiodata/RawAudioBuffer.hpp"
#include "core/audiodata/RawSample.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

RawAudioBuffer::RawAudioBuffer(AudioInfo info){
	mInfo = info;
	resize(mInfo.Samples);
	return;
}

RawAudioBuffer::RawAudioBuffer(unsigned int channels, unsigned long samples, unsigned long offset, unsigned int samplerate){
	mInfo.Channels = channels;
	mInfo.Samples = samples;
	mInfo.Offset = offset;
	mInfo.Samplerate = samplerate;
	resize(mInfo.Samples);
	return;
}

RawAudioBuffer::~RawAudioBuffer(){
	return;
}

ISample& RawAudioBuffer::operator[](unsigned long pos){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw OutOfBoundsException();
	return *createSample(pos);
}

void RawAudioBuffer::operator=(IAudioBuffer &data){
	mInfo = data.getInfo();
	resize(mInfo.Samples);
	for(unsigned int i = 0; i < mInfo.Samples; i++){
		set(i, data[i]);
	}
}

ISample* RawAudioBuffer::get(unsigned long pos){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw OutOfBoundsException();
	return createSample(pos);
}

void RawAudioBuffer::set(unsigned long pos, ISample &data){
	if(pos >= mData.size() + mInfo.Offset || pos < mInfo.Offset) throw OutOfBoundsException();
	if(data.getChannels() != mInfo.Channels) throw ChannelsException();
	for(unsigned int i = 0; i < mInfo.Channels; i++){
		mData[(pos - mInfo.Offset) * mInfo.Channels + i] = data[i];
	}
	return;
}

void RawAudioBuffer::resize(unsigned long samples){
	mData.resize(samples * mInfo.Channels);
}

void RawAudioBuffer::setInfo(const AudioInfo &info){
	if(info.Channels != mInfo.Channels) throw ChannelsException();
	mInfo = info;
}

const AudioInfo RawAudioBuffer::getInfo(){
	return mInfo;
}

ISample* RawAudioBuffer::createSample(unsigned long pos){
    return new RawSample(&mData[(pos - mInfo.Offset) * mInfo.Channels], mInfo.Channels);
}

} // maudio






