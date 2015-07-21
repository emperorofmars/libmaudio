/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiodata/AudioQueue.hpp"
#include <iostream>
#include <cmath>

namespace maudio{

AudioQueue::AudioQueue(AudioInfo info){
	mAudioInfo = info;
}

void AudioQueue::push(Sample data){
	mMutex.lock();
	if(data.getChannels() == getChannels()){
		mData.push_back(data);
		mAudioInfo.Samples++;
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
		mAudioInfo.Offset++;
		mAudioInfo.Samples--;
	}
	else{
		std::cerr << "POP ERROR" << std::endl;
	}
	mMutex.unlock();
	return ret;
}

Sample AudioQueue::get(unsigned long pos){
	Sample ret(getChannels());
	if(pos < mAudioInfo.Offset + mAudioInfo.Samples && pos >= mAudioInfo.Offset){
		ret = mData[pos - mAudioInfo.Offset];
	}
	return ret;
}

unsigned int AudioQueue::getChannels(){
	return mAudioInfo.Channels;
}

unsigned int AudioQueue::size(){
	return mData.size();
}

AudioInfo AudioQueue::getAudioInfo(){
	return mAudioInfo;
}

void AudioQueue::setAudioInfo(AudioInfo info){
	mAudioInfo = info;
	return;
}


} // maudio



