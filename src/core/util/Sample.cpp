/*
 * Holds a single sample of audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/util/Sample.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

Sample::Sample(unsigned int channels){
	mData.resize(channels);
}

Sample::Sample(const std::vector<float> data){
	mData = data;
}

Sample::~Sample(){
}

float& Sample::operator[](unsigned int pos){
	if(pos >= mData.size()) throw ChannelsException();
	return mData[pos];
}

void Sample::operator=(ISample &data){
	if(data.getChannels() != mData.size()) throw ChannelsException();
	for(unsigned int i = 0; i < mData.size(); i++){
		mData[i] = data[i];
	}
	return;
}

float Sample::get(unsigned int pos){
	if(pos >= mData.size()) throw ChannelsException();
	return mData[pos];
}

void Sample::set(float data, unsigned int pos){
	if(pos >= mData.size()) throw ChannelsException();
	mData[pos] = data;
}

unsigned int Sample::getChannels(){
	return mData.size();
}

} // maudio



