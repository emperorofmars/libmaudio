/*
 * Holds a single sample of audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_RAWSAMPLE
#define MAUDIO_RAWSAMPLE

#include "core/audiodata/ISample.hpp"
#include <vector>

namespace maudio{

///ISample implementation with raw pointers to a RawAudioBuffer
class RawSample : public ISample{
public:
	RawSample(unsigned int channels = 1);
	RawSample(float *data, unsigned int channels); ///ugly C style, but allows faster loading of audio
	virtual ~RawSample();

	virtual float& operator[](unsigned int pos);
	virtual void operator=(ISample &data);
	virtual float get(unsigned int pos) const;
	virtual void set(unsigned int pos, float data);
	virtual unsigned int getChannels() const;

private:
	float *mData; ///one value per channel
	unsigned int mChannels;
	bool mOwner;
};

} // maudio

#endif // MAUDIO_RAWSAMPLE


