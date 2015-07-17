/*
 * Holds an audio stream
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_IAUDIOBUFFER
#define MAUDIO_IAUDIOBUFFER

#include "ISample.hpp"
#include "AudioInfo.hpp"

namespace maudio{

///holds an audio stream
class IAudioBuffer{
public:
	virtual ~IAudioBuffer(){};

	virtual ISample& operator[](unsigned long pos) = 0;
	virtual void operator=(IAudioBuffer &data) = 0;
	virtual ISample& get(unsigned long pos) = 0;
	virtual void set(ISample &data, unsigned long pos) = 0;

	virtual void resize(unsigned long samples) = 0;
	virtual void setInfo(const AudioInfo &info) = 0;
	virtual const AudioInfo getInfo() = 0;
};

} // maudio

#endif // MAUDIO_IAUDIOBUFFER


