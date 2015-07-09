/*
 * Holds a single sample of audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/util/Sample.hpp"

namespace maudio{

Sample::Sample(){
}

Sample::Sample(std::vector<float> data){
	mData = data;
}

Sample::~Sample(){
}

float Sample::operator[](unsigned char i){
	if(i >= mData.size()) return 0;
	return mData[i];
}

std::vector<float> Sample::get(){
	return mData;
}

void Sample::set(std::vector<float> data){
	mData = data;
}

unsigned int Sample::getChannels(){
	return mData.size();
}

} // maudio



