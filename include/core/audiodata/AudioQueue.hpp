/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_AUDIOQUEUE
#define MAUDIO_AUDIOQUEUE

#include "core/audiodata/Sample.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <deque>
#include <mutex>

namespace maudio{

class AudioQueue{
public:
	AudioQueue(IAudioInfo &info);

	void push(Sample data);
	Sample pop();

	Sample get(unsigned long pos);

	unsigned int getChannels();
	unsigned int size();

	AudioInfo getAudioInfo();
	void setAudioInfo(IAudioInfo &info);

private:
	AudioInfo mAudioInfo;
	std::deque<Sample> mData;
	std::mutex mMutex;
};

} // maudio

#endif // MAUDIO_AUDIOQUEUE


