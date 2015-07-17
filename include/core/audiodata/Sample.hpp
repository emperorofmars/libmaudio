/*
 * Holds a single sample of audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_SAMPLE
#define MAUDIO_SAMPLE

#include "ISample.hpp"
#include <vector>

namespace maudio{

///ISample implementation with vectors
class Sample : public ISample{
public:
	Sample(unsigned int channels = 1);
	Sample(const std::vector<float> data);
	virtual ~Sample();

	virtual float& operator[](unsigned int pos);
	virtual void operator=(ISample &data);
	virtual float get(unsigned int pos);
	virtual void set(float data, unsigned int pos);
	virtual unsigned int getChannels();

private:
	std::vector<float> mData; ///one value per channel
};

} // maudio

#endif // MAUDIO_SAMPLE


