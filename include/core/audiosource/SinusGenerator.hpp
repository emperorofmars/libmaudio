/*
 * Generates a sinus
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_SINUSGENERATOR
#define MAUDIO_SINUSGENERATOR

#include "core/audiosource/BaseAudioSource.hpp"

namespace maudio{

class SinusGenerator : public BaseAudioSource{
public:
	SinusGenerator();
	virtual ~SinusGenerator();

	virtual void setFrequency(float freq);

    virtual Sample get(unsigned long pos);
    virtual AudioInfo getAudioInfo();

protected:
	AudioInfo mAudioInfo;
	float mFreq;
};

} // maudio

#endif // MAUDIO_SINUSGENERATOR


