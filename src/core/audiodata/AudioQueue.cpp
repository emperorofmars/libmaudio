/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiodata/AudioQueue.hpp"
#include <iostream>
#include <cmath>

namespace maudio{

AudioQueue::AudioQueue(AudioInfo info){
	mAudioInfo = info;
}

void AudioQueue::push(Sample data){
	if(data.getChannels() == getChannels()){
		mData.push_back(data);
		mAudioInfo.Samples++;
	}
	return;
}

Sample AudioQueue::pop(){
	Sample ret(getChannels());
	if(mData.size() <= mOffset){
		std::cerr << "POP ERROR" << std::endl;
	}
	if(mData.size() > mOffset){
		ret = mData[mOffset];
		//ret = mData.front();
		//mData.pop_front();
		mAudioInfo.Offset++;
		mAudioInfo.Samples--;
	}
	//std::cerr << "size: " << mData.size() << " " << mOffset << std::endl;
	mOffset++;
	return ret;
}

Sample AudioQueue::get(unsigned long pos){
	Sample ret(getChannels());
	if(pos < mAudioInfo.Offset + mAudioInfo.Samples && pos >= mAudioInfo.Offset){
		ret = mData[pos - mAudioInfo.Offset];
	}
	return ret;
}

void AudioQueue::lock(){
	mMutex.lock();
	return;
}

void AudioQueue::unlock(){
	mMutex.unlock();
	return;
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



