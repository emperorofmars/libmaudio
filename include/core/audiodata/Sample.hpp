/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
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
	~Sample();

	const float operator[](unsigned int pos) const;
	void operator=(const Sample &data);
	float get(unsigned int pos) const;
	void set(unsigned int pos, float data);
	unsigned int getChannels() const;

	Sample operator+(const Sample &data);
	Sample operator-(const Sample &data);
	Sample operator*(const Sample &data);
	Sample operator/(const Sample &data);

	Sample operator*(float data);
	Sample operator/(float data);

	void operator+=(const Sample &data);
	void operator-=(const Sample &data);
	void operator*=(const Sample &data);
	void operator/=(const Sample &data);

	void operator*=(float data);
	void operator/=(float data);

private:
	std::vector<float> mData; ///one value per channel
};

} // maudio

#endif // MAUDIO_SAMPLE


