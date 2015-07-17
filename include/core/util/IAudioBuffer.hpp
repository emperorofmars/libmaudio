/*
 * Holds an audio stream
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_IAUDIOBUFFER
#define MAUDIO_IAUDIOBUFFER

#include "core/util/ISample.hpp"
#include "core/util/AudioInfo.hpp"

namespace maudio{

///holds an audio stream
class IAudioBuffer{
public:
	IAudioBuffer(AudioInfo info) = 0;
	IAudioBuffer(unsigned int channels, unsigned long samples, unsigned long offset, unsigned int samplerate) = 0;
	virtual ~IAudioBuffer(){};

	virtual Sample operator[](unsigned long sample);
	virtual Sample get(unsigned long pos);
	virtual void set(Sample data, unsigned long pos);

	virtual void setLength();
	virtual void setInfo(AudioInfo info);
	virtual AudioInfo getInfo();
};

} // maudio

#endif // MAUDIO_IAUDIOBUFFER


