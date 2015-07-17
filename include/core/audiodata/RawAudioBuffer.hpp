/*
 * Holds an audio stream
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_RAWAUDIOBUFFER
#define MAUDIO_RAWAUDIOBUFFER

#include "core/audiodata/IAudioBuffer.hpp"
#include "core/audiodata/ISample.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <vector>

namespace maudio{

///holds an audio stream in a vector of floats
class RawAudioBuffer : public IAudioBuffer{
public:
	RawAudioBuffer(AudioInfo info);
	RawAudioBuffer(unsigned int channels = 1, unsigned long samples = 0, unsigned long offset = 0, unsigned int samplerate = 44100);
	virtual ~RawAudioBuffer();

	virtual ISample& operator[](unsigned long pos);
	virtual void operator=(IAudioBuffer &data);
	virtual ISample& get(unsigned long pos);
	virtual void set(ISample &data, unsigned long pos);

	virtual void resize(unsigned long samples);
	virtual void setInfo(const AudioInfo &info);
	virtual const AudioInfo getInfo();

private:
	ISample* createSample(unsigned long pos);

	std::vector<float> mData;
	AudioInfo mInfo;
};

} // maudio

#endif // MAUDIO_RAWAUDIOBUFFER


