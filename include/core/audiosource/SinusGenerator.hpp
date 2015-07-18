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

	virtual void setLength(unsigned long samples);
	virtual unsigned long getLength();
	virtual void setFrequency(float freq);

    virtual Sample get(unsigned long pos, int output);
    virtual int getMaxOutput();
    virtual AudioInfo getAudioInfo();
    virtual FileInfo getFileInfo();

protected:
	AudioInfo mAudioInfo;
	FileInfo mFileInfo;
	float mFreq;
};

} // maudio

#endif // MAUDIO_SINUSGENERATOR


