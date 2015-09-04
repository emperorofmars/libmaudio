/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SINUSGENERATOR
#define MAUDIO_SINUSGENERATOR

#include "core/action/BaseAction.hpp"
#include "core/property/SimpleProperty.hpp"
#include "core/property/SimpleKeyableProperty.hpp"
#include <memory>

namespace maudio{

class SinusGenerator : public BaseAction{
public:
	SinusGenerator();
	virtual ~SinusGenerator();
	
	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept;
	virtual IAudioInfo *getInfo() noexcept;

	virtual int MaxInputs() const;
	virtual bool HasOutputs() const;

	virtual void readConfig(const IKeyValueStore *conf);

	virtual void setFrequency(float freq);
	virtual void setSamplerate(unsigned int samplerate);
	virtual void setChannels(unsigned int channels);

	virtual void serialize(IMultiLevelStore *data) const;
	virtual void deserialize(const IMultiLevelStore *data);

private:
	AudioInfo mAudioInfo;
	std::shared_ptr<KeyableFloatProperty> mFreq;
	std::shared_ptr<UIntProperty> mSamplerate;
	std::shared_ptr<UIntProperty> mChannels;
};

} // maudio

#endif // MAUDIO_SINUSGENERATOR


