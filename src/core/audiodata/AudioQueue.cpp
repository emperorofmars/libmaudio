/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiodata/AudioQueue.hpp"

namespace maudio{

AudioQueue::AudioQueue(AudioInfo info){
	mAudioInfo = info;
	mChannels = mAudioInfo.Channels;
}

void AudioQueue::push(Sample data){
	if(data.getChannels() == mChannels){
		mData.push_back(data);
		mAudioInfo.Samples++;
	}
	return;
}

Sample AudioQueue::pop(){
	Sample ret(getChannels());
	if(mData.size() > 0){
		ret = mData.front();
		mData.pop_front();
		mAudioInfo.Offset++;
		mAudioInfo.Samples--;
	}
	return ret;
}

Sample& AudioQueue::get(unsigned long pos){
	Sample ret(mChannels);
	if(pos < mAudioInfo.Offset + mAudioInfo.Samples && pos >= mAudioInfo.Offset) ret = mData[pos - mAudioInfo.Offset];
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



