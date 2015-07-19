/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiodata/AudioQueue.hpp"

namespace maudio{

AudioQueue::AudioQueue(unsigned int channels){
	mChannels = channels;
}

void AudioQueue::push(Sample data){
	if(data.getChannels() == mChannels) mData.push_back(data);
	mAudioInfo.Samples++;
	return;
}

Sample AudioQueue::pop(){
	Sample ret = mData.front();
	mData.pop_front();
	mAudioInfo.Offset++;
	mAudioInfo.Samples--;
	return ret;
}

Sample AudioQueue::get(unsigned long pos){
	if(pos < mAudioInfo.Offset + mAudioInfo.Samples && pos >= mAudioInfo.Offset) return mData[pos - mAudioInfo.Offset];
	return Sample(mChannels);
}

unsigned int AudioQueue::getChannels(){
	return mChannels;
}

AudioInfo AudioQueue::getAudioInfo(){
	return mAudioInfo;
}

void AudioQueue::setAudioInfo(AudioInfo info){
	mAudioInfo = info;
	return;
}


} // maudio



