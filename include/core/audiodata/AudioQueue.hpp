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

namespace maudio{

class AudioQueue{
public:
	AudioQueue(unsigned int channels);

	void push(Sample data);
	Sample pop();

	Sample get(unsigned long pos);

	unsigned int getChannels();

	AudioInfo getAudioInfo();
	void setAudioInfo(AudioInfo info);

private:
	unsigned int mChannels;
	AudioInfo mAudioInfo;
	std::deque<Sample> mData;
};

} // maudio

#endif // MAUDIO_AUDIOQUEUE


