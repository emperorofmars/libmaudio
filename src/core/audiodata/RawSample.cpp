/*
 * Holds a single sample of audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiodata/RawSample.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

RawSample::RawSample(unsigned int channels){
	mData = new float[channels];
	mChannels = channels;
	mOwner = true;
}

RawSample::RawSample(float *data, unsigned int channels){
	mData = data;
	mChannels = channels;
	mOwner = false;
}

RawSample::~RawSample(){
	if(mOwner) delete []mData;
}

float& RawSample::operator[](unsigned int pos){
	if(pos >= mChannels) throw ChannelsException();
	return mData[pos];
}

void RawSample::operator=(ISample &data){
	if(data.getChannels() != mChannels) throw ChannelsException();
	for(unsigned int i = 0; i < mChannels; i++){
		mData[i] = data[i];
	}
	return;
}

float RawSample::get(unsigned int pos) const{
	if(pos >= mChannels) throw ChannelsException();
	return mData[pos];
}

void RawSample::set(unsigned int pos, float data){
	if(pos >= mChannels) throw ChannelsException();
	mData[pos] = data;
}

unsigned int RawSample::getChannels() const{
	return mChannels;
}

} // maudio



