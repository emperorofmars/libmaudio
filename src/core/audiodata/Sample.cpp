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
	*this = data;
	return;
}

Sample::~Sample(){
}

const float Sample::operator[](unsigned int pos) const{
	if(pos >= mData.size()) return 0;
	return mData[pos];
}

void Sample::operator=(const Sample &data){
	mData = data.mData;
	return;
}

float Sample::get(unsigned int pos) const{
	if(pos >= mData.size()) return 0;
	return mData[pos];
}

void Sample::set(float data, unsigned int pos){
	if(pos >= mData.size()) return;
	mData[pos] = data;
}

unsigned int Sample::getChannels() const{
	return mData.size();
}

Sample Sample::operator+(const Sample &data){
	Sample ret(*this);
	if(getChannels() == data.getChannels()){
		for(unsigned int i = 0; i < getChannels(); i++){
			ret.set(ret[i] + data[i], i);
		}
	}
	return ret;
}

Sample Sample::operator-(const Sample &data){
	Sample ret(*this);
	if(getChannels() == data.getChannels()){
		for(unsigned int i = 0; i < getChannels(); i++){
			ret.set(ret[i] - data[i], i);
		}
	}
	return ret;
}

Sample Sample::operator*(const Sample &data){
	Sample ret(*this);
	if(getChannels() == data.getChannels()){
		for(unsigned int i = 0; i < getChannels(); i++){
			ret.set(ret[i] * data[i], i);
		}
	}
	return ret;
}

Sample Sample::operator/(const Sample &data){
	Sample ret(*this);
	if(getChannels() == data.getChannels()){
		for(unsigned int i = 0; i < getChannels(); i++){
			if(data[i] != 0) ret.set(ret[i] / data[i], i);
		}
	}
	return ret;
}

Sample Sample::operator*(float data){
	Sample ret(*this);
    for(unsigned int i = 0; i < getChannels(); i++){
        ret.set(ret[i] * data, i);
    }
	return ret;
}

Sample Sample::operator/(float data){
	Sample ret(*this);
	if(data == 0) Sample(getChannels());
    for(unsigned int i = 0; i < getChannels(); i++){
        ret.set(ret[i] / data, i);
    }
	return ret;
}

void Sample::operator+=(const Sample &data){
	if(getChannels() == data.getChannels()){
		for(unsigned int i = 0; i < getChannels(); i++){
			mData[i] += data[i];
		}
	}
	return;
}

void Sample::operator-=(const Sample &data){
	if(getChannels() == data.getChannels()){
		for(unsigned int i = 0; i < getChannels(); i++){
			mData[i] -= data[i];
		}
	}
	return;
}

void Sample::operator*=(const Sample &data){
	if(getChannels() == data.getChannels()){
		for(unsigned int i = 0; i < getChannels(); i++){
			mData[i] *= data[i];
		}
	}
	return;
}

void Sample::operator/=(const Sample &data){
	if(getChannels() == data.getChannels()){
		for(unsigned int i = 0; i < getChannels(); i++){
			if(data[i] != 0) mData[i] /= data[i];
		}
	}
	return;
}

void Sample::operator*=(float data){
    for(unsigned int i = 0; i < getChannels(); i++){
        mData[i] *= data;
    }
	return;
}

void Sample::operator/=(float data){
	if(data == 0) return;
    for(unsigned int i = 0; i < getChannels(); i++){
        mData[i] /= data;
    }
	return;
}

} // maudio








