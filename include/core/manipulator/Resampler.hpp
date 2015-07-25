/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_RESAMPLER
#define MAUDIO_RESAMPLER

#include "core/manipulator/BaseManipulator.hpp"

namespace maudio{

class Resampler : public BaseManipulator{
public:
	Resampler(unsigned int samplerate = 44100);
	virtual ~Resampler();

	virtual AudioBuffer get(unsigned long pos, unsigned int length) noexcept;
	virtual AudioInfo getInfo() noexcept;
	virtual int MaxInputs() const;
	virtual bool checkIfCompatible(std::shared_ptr<Node> node, int slot = -1);

	virtual void setSampleRate(unsigned int samplerate);
	virtual unsigned int getSampleRate();

private:
	unsigned int mOutputSamplerate;
};

} // maudio

#endif // MAUDIO_RESAMPLER
