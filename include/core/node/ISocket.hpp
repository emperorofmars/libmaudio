/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ISOCKET
#define MAUDIO_ISOCKET

#include "core/audiodata/IAudioBuffer.hpp"
#include "core/audiodata/IAudioInfo.hpp"

namespace maudio{

class ISocket{
public:
	virtual ~ISocket(){};

	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept = 0;
	virtual IAudioInfo *getInfo() noexcept = 0;

	virtual void deleteBuffer(IAudioBuffer *data) noexcept = 0;
	virtual void deleteInfo(IAudioInfo *data) noexcept = 0;
	virtual void deleteSample(ISample *data) noexcept = 0;
};

} // maudio

#endif // MAUDIO_HEADER




