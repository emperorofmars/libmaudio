/*
 * Holds an audio stream
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_AUDIOBUFFER
#define MAUDIO_AUDIOBUFFER

#include "IAudioBuffer.hpp"
#include "ISample.hpp"
#include "AudioInfo.hpp"
#include <vector>

namespace maudio{

///holds an audio stream in a vector of ISamples
class AudioBuffer : public IAudioBuffer{
public:
	AudioBuffer(AudioInfo info);
	AudioBuffer(unsigned int channels = 1, unsigned long samples = 0, unsigned long offset = 0, unsigned int samplerate = 44100);
	virtual ~AudioBuffer();

	virtual ISample& operator[](unsigned long pos);
	virtual void operator=(IAudioBuffer &data);
	virtual ISample& get(unsigned long pos);
	virtual void set(ISample &data, unsigned long pos);

	virtual void resize(unsigned long samples);
	virtual void setInfo(const AudioInfo &info);
	virtual const AudioInfo getInfo();

private:
	std::vector<ISample*> mData;
	AudioInfo mInfo;
};

} // maudio

#endif // MAUDIO_AUDIOBUFFER


