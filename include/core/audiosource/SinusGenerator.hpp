/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SINUSGENERATOR
#define MAUDIO_SINUSGENERATOR

#include "core/audiosource/BaseAudioSource.hpp"

namespace maudio{

class SinusGenerator : public BaseAudioSource{
public:
	SinusGenerator();
	virtual ~SinusGenerator();

    virtual Sample get(unsigned long pos) noexcept;
    virtual AudioInfo getInfo() noexcept;
    virtual bool checkIfCompatible(std::shared_ptr<Node> node, int slot = -1);

	virtual void setFrequency(float freq);

protected:
	AudioInfo mAudioInfo;
	float mFreq;
};

} // maudio

#endif // MAUDIO_SINUSGENERATOR


