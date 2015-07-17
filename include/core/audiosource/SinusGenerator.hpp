/*
 * Generates a sinus
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_SINUSGENERATOR
#define MAUDIO_SINUSGENERATOR

#include "core/audiosource/IAudioGenerator.hpp"

namespace maudio{

class SinusGenerator : public IAudioGenerator{
public:
	SinusGenerator();
	virtual ~SinusGenerator();

	virtual void setLength(unsigned long samples);
	virtual unsigned long getLength();
	virtual void setFrequency(float freq);

    virtual ISample* get(unsigned long pos);
    virtual AudioInfo getAudioInfo();
    virtual FileInfo getFileInfo();

private:
	AudioInfo mAudioInfo;
	FileInfo mFileInfo;
	float mFreq;
};

} // maudio

#endif // MAUDIO_SINUSGENERATOR


