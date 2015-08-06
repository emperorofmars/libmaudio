/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SINUSGENERATOR
#define MAUDIO_SINUSGENERATOR

#include "core/node/IAction.hpp"
#include "core/property/SimpleProperty.hpp"
#include "core/property/SimpleKeyableProperty.hpp"

namespace maudio{

class SinusGenerator : public BaseAudioSource{
public:
	SinusGenerator();
	virtual ~SinusGenerator();

    virtual AudioBuffer get(unsigned long pos, unsigned int length) noexcept;
    virtual AudioInfo getInfo() noexcept;
    virtual bool checkIfCompatible(std::shared_ptr<Node> node, int slot = -1);
	virtual void readConfig(const Config &conf);

	virtual void setFrequency(float freq);
	virtual void setSamplerate(unsigned int samplerate);
	virtual void setChannels(unsigned int channels);

private:
	AudioInfo mAudioInfo;
	std::shared_ptr<KeyableFloatProperty> mFreq;
	std::shared_ptr<UIntProperty> mSamplerate;
	std::shared_ptr<UIntProperty> mChannels;
};

} // maudio

#endif // MAUDIO_SINUSGENERATOR


