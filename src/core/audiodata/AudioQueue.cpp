/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiodata/AudioQueue.hpp"
#include <iostream>
#include <cmath>

namespace maudio{

AudioQueue::AudioQueue(IAudioInfo &info){
	mAudioInfo = info;
}

void AudioQueue::push(Sample data){
	mMutex.lock();
	if(data.getChannels() == getChannels()){
		mData.push_back(data);
		mAudioInfo.setSamples(mAudioInfo.getSamples() + 1);
	}
	mMutex.unlock();
	return;
}

Sample AudioQueue::pop(){
	mMutex.lock();
	Sample ret(getChannels());
	if(mData.size() > 0){
		ret = mData.front();
		mData.pop_front();
		mAudioInfo.setOffset(mAudioInfo.getOffset() + 1);
		mAudioInfo.setSamples(mAudioInfo.getSamples() - 1);
	}
	else{
		std::cerr << "POP ERROR" << std::endl;
	}
	mMutex.unlock();
	return ret;
}

Sample AudioQueue::get(unsigned long pos){
	Sample ret(getChannels());
	if(pos < mAudioInfo.getOffset() + mAudioInfo.getSamples() && pos >= mAudioInfo.getOffset()){
		ret = mData[pos - mAudioInfo.getOffset()];
	}
	return ret;
}

unsigned int AudioQueue::getChannels(){
	return mAudioInfo.getChannels();
}

unsigned int AudioQueue::size(){
	return mData.size();
}

AudioInfo AudioQueue::getAudioInfo(){
	return mAudioInfo;
}

void AudioQueue::setAudioInfo(IAudioInfo &info){
	mAudioInfo = info;
	return;
}


} // maudio



