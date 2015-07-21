/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiodata/Sample.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

Sample::Sample(unsigned int channels){
	mData.resize(channels);
}

Sample::Sample(const std::vector<float> data){
	mData = data;
}

Sample::Sample(const Sample &data){
	if(data.getChannels() != mData.size()) mData.resize(data.getChannels());
	for(unsigned int i = 0; i < mData.size(); i++){
		mData[i] = data[i];
	}
	return;
}

Sample::~Sample(){
}

const float& Sample::operator[](unsigned int pos) const{
	if(pos >= mData.size()) throw ChannelsException();
	return mData[pos];
}

void Sample::operator=(const Sample &data){
	if(data.getChannels() != mData.size()) mData.resize(data.getChannels());
	for(unsigned int i = 0; i < mData.size(); i++){
		mData[i] = data[i];
	}
	return;
}

float Sample::get(unsigned int pos) const{
	if(pos >= mData.size()) throw ChannelsException();
	return mData[pos];
}

void Sample::set(unsigned int pos, float data){
	if(pos >= mData.size()) throw ChannelsException();
	mData[pos] = data;
}

unsigned int Sample::getChannels() const{
	return mData.size();
}

} // maudio



