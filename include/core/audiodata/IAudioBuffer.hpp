/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IAUDIOBUFFER
#define MAUDIO_IAUDIOBUFFER

#include "core/audiodata/ISample.hpp"
#include "core/audiodata/IAudioInfo.hpp"

namespace maudio{

///holds an audio stream in a vector of floats
class IAudioBuffer{
public:
	virtual ~IAudioBuffer(){};

	virtual ISample *operator[](unsigned long pos) const = 0;
	virtual ISample *get(unsigned long pos) const = 0;
	virtual void set(const ISample &data, unsigned long pos) = 0;

	virtual void resize(unsigned long samples) = 0;
	virtual const IAudioInfo *getInfo() const = 0;

	virtual const float* getRaw() const = 0;
};

} // maudio

#endif // MAUDIO_IAUDIOBUFFER


