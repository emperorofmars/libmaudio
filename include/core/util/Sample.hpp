/*
 * Holds a single sample of audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_SAMPLE
#define MAUDIO_SAMPLE

#include <vector>

namespace maudio{

///holds a frame of audio
class Sample{
public:
	Sample();
	Sample(std::vector<float> data);
	~Sample();

	std::vector<float> get();
	float operator[](unsigned char i);
	void set(std::vector<float> data);
	unsigned int getChannels();

private:
	std::vector<float> mData; ///one value per channel
};

} // maudio

#endif // MAUDIO_SAMPLE


