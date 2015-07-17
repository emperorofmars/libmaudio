/*
 * Interface for generating Audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_IAUDIOGENERATOR
#define MAUDIO_IAUDIOGENERATOR

#include "core/audiosource/IAudioSource.hpp"

namespace maudio{

class IAudioGenerator : public IAudioSource{
public:
	virtual ~IAudioGenerator(){};

	virtual void setLength(unsigned long samples) = 0;
	virtual unsigned long getLength() = 0;
};

} // maudio

#endif // MAUDIO_IAUDIOGENERATOR


