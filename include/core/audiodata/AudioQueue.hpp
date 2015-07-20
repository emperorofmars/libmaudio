/*
 * Class for queuing audiostreams
 *
 * Copyright (C) 2015 Martin Schwarz
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
	AudioQueue(AudioInfo info);

	void push(Sample data);
	Sample pop();

	Sample get(unsigned long pos);

	void lock();
	void unlock();

	unsigned int getChannels();
	unsigned int size();

	AudioInfo getAudioInfo();
	void setAudioInfo(AudioInfo info);

private:
	unsigned int mOffset = 0;
	AudioInfo mAudioInfo;
	std::deque<Sample> mData;
	std::mutex mMutex;
};

} // maudio

#endif // MAUDIO_AUDIOQUEUE


