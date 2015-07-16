/*
 * Holds a single sample of audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/util/Sample.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

Sample::Sample(){
}

Sample::Sample(std::vector<float> data){
	mData = data;
}

Sample::~Sample(){
}
/*
float Sample::operator[](unsigned char i){
	if(i >= mData.size()) throw ChannelsException();
	return mData[i];
}
*/
float& Sample::operator[](unsigned int i){
	return mData[i];
}

float Sample::get(unsigned char i){
	if(i >= mData.size()) throw ChannelsException();
	return mData[i];
}

std::vector<float> Sample::get(){
	return mData;
}

void Sample::set(std::vector<float> data){
	mData = data;
}

void Sample::set(int position, float data){
	if(position >= mData.size()) throw ChannelsException();
	mData[position] = data;
}

unsigned int Sample::getChannels(){
	return mData.size();
}

} // maudio



