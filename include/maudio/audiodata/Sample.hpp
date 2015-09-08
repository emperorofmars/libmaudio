/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SAMPLE
#define MAUDIO_SAMPLE

#include "maudio/audiodata/ISample.hpp"
#include <vector>

namespace maudio{

///Holds a sample of audio
class Sample : public ISample{
public:
	Sample(unsigned int channels);
	Sample(const std::vector<float> &data);
	Sample(const ISample &data);
	virtual ~Sample();

	virtual const float operator[](unsigned int pos) const;
	virtual void operator=(const ISample &data);
	virtual float get(unsigned int pos) const;
	virtual void set(float data, unsigned int pos);
	virtual unsigned int getChannels() const;

	virtual ISample *operator+(const ISample &data);
	virtual ISample *operator-(const ISample &data);
	virtual ISample *operator*(const ISample &data);
	virtual ISample *operator/(const ISample &data);

	virtual ISample *operator*(float data);
	virtual ISample *operator/(float data);

	virtual void operator+=(const ISample &data);
	virtual void operator-=(const ISample &data);
	virtual void operator*=(const ISample &data);
	virtual void operator/=(const ISample &data);

	virtual void operator*=(float data);
	virtual void operator/=(float data);

private:
	std::vector<float> mData; ///one value per channel
};

} // maudio

#endif // MAUDIO_SAMPLE


