/*
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_SAMPLE
#define MAUDIO_SAMPLE

#include <vector>

namespace maudio{

///Holds a sample of audio
class Sample{
public:
	Sample(unsigned int channels);
	Sample(const std::vector<float> data);
	Sample(const Sample &data);
	virtual ~Sample();

	virtual const float& operator[](unsigned int pos) const;
	virtual void operator=(const Sample &data);
	virtual float get(unsigned int pos) const;
	virtual void set(unsigned int pos, float data);
	virtual unsigned int getChannels() const;

private:
	std::vector<float> mData; ///one value per channel
};

} // maudio

#endif // MAUDIO_SAMPLE


