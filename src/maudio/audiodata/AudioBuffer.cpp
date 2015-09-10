/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/audiodata/AudioBuffer.hpp"
#include "maudio/util/AudioException.hpp"

namespace maudio{

AudioBuffer::AudioBuffer(IAudioInfo &info){
	mInfo = info;
	resize(mInfo.getSamples());
	return;
}

AudioBuffer::AudioBuffer(unsigned int channels, unsigned long samples, unsigned long offset, unsigned int samplerate){
	mInfo.setChannels(channels);
	mInfo.setSamples(samples);
	mInfo.setOffset(offset);
	mInfo.setSamplerate(samplerate);
	resize(mInfo.getSamples());
	return;
}

AudioBuffer::AudioBuffer(const AudioBuffer &data){
	*this = data;
	return;
}

AudioBuffer::~AudioBuffer(){
	return;
}

ISample *AudioBuffer::operator[](unsigned long pos) const{
	return createSample(pos);
}

void AudioBuffer::operator=(const IAudioBuffer &data){
	mInfo = *data.getInfo();
	mData.assign(data.getRaw(), data.getRaw() + data.getInfo()->getSamples() * data.getInfo()->getChannels());
	resize(mInfo.getSamples());
	return;
}

ISample *AudioBuffer::get(unsigned long pos) const{
	return createSample(pos);
}

void AudioBuffer::deleteSample(ISample *data){
	if(data) delete data;
	return;
}

void AudioBuffer::set(const ISample &data, unsigned long pos){
	if(pos >= mData.size()) return;
	if(data.getChannels() != mInfo.getChannels()) return;
	for(unsigned int i = 0; i < mInfo.getChannels(); i++){
		mData[pos * mInfo.getChannels() + i] = data.get(i);
	}
	return;
}

void AudioBuffer::resize(unsigned long samples){
	mData.resize(samples * mInfo.getChannels());
	return;
}

const IAudioInfo *AudioBuffer::getInfo() const{
	return &mInfo;
}

float *AudioBuffer::getRaw() const{
	return (float *)&mData[0];
}

Sample *AudioBuffer::createSample(unsigned long pos) const{
	if(pos >= mData.size()) return new Sample(mInfo.getChannels());
    return new Sample(std::vector<float>(mData.begin() + (pos) * mInfo.getChannels(), mData.begin() + (pos + 1) * mInfo.getChannels()));
}

} // maudio






