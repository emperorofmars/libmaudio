/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_AUDIOBUFFER
#define MAUDIO_AUDIOBUFFER

#include "core/audiodata/Sample.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <vector>

namespace maudio{

///holds an audio stream in a vector of floats
class AudioBuffer{
public:
	AudioBuffer(AudioInfo info);
	AudioBuffer(unsigned int channels = 1, unsigned long samples = 0, unsigned long offset = 0, unsigned int samplerate = 44100);
	virtual ~AudioBuffer();

	virtual Sample operator[](unsigned long pos);
	virtual void operator=(AudioBuffer &data);
	virtual Sample get(unsigned long pos);
	virtual void set(unsigned long pos, Sample &data);

	virtual void resize(unsigned long samples);
	virtual void setInfo(const AudioInfo &info);
	virtual const AudioInfo getInfo();

private:
	Sample createSample(unsigned long pos);

	std::vector<float> mData;
	AudioInfo mInfo;
};

} // maudio

#endif // MAUDIO_AUDIOBUFFER


