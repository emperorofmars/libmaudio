/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_AUDIOBUFFER
#define MAUDIO_AUDIOBUFFER

#include "core/audiodata/IAudioBuffer.hpp"
#include "core/audiodata/Sample.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <vector>

namespace maudio{

///holds an audio stream in a vector of floats
class AudioBuffer : public IAudioBuffer{
public:
	AudioBuffer(IAudioInfo &info);
	AudioBuffer(unsigned int channels = 1, unsigned long samples = 0, unsigned long offset = 0, unsigned int samplerate = 44100);
	AudioBuffer(const AudioBuffer &data);
	virtual ~AudioBuffer();

	virtual ISample *operator[](unsigned long pos) const;
	virtual void operator=(const IAudioBuffer &data);
	virtual ISample *get(unsigned long pos) const;
	virtual void deleteSample(ISample *data);

	virtual void set(const ISample &data, unsigned long pos);

	virtual void resize(unsigned long samples);
	virtual const IAudioInfo *getInfo() const;

	virtual const float* getRaw() const;

private:
	Sample *createSample(unsigned long pos) const;

	std::vector<float> mData;
	AudioInfo mInfo;
};

} // maudio

#endif // MAUDIO_AUDIOBUFFER


