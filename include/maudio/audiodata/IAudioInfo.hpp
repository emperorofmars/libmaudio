/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IAUDIOINFO
#define MAUDIO_IAUDIOINFO

#include "maudio/serializer/ISerializable.hpp"

namespace maudio{

class IAudioInfo : public ISerializable{
public:
	virtual ~IAudioInfo(){};

	virtual unsigned long getSamples() const = 0;
	virtual unsigned long getOffset() const = 0;
	virtual unsigned int getSamplerate() const = 0;
	virtual unsigned int getChannels() const = 0;

	virtual void setSamples(unsigned long samples) = 0;
	virtual void setOffset(unsigned long offset) = 0;
	virtual void setSamplerate(unsigned int samplerate) = 0;
	virtual void setChannels(unsigned int channels) = 0;
};

} // maudio

#endif // MAUDIO_IAUDIOINFO


