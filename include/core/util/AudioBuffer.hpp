/*
 * Holds an audio stream
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BUFFER
#define MAUDIO_BUFFER

#include <vector>
#include "core/util/Sample.hpp"
#include "core/util/AudioInfo.hpp"

namespace maudio{

///holds an audio stream
class AudioBuffer{
public:
	AudioBuffer();
	~AudioBuffer();

    void setLength(unsigned long samples);

    std::vector<float> get();
    Sample get(unsigned long sample);
	Sample operator[](unsigned long sample);
    void set(unsigned long sample, Sample data);

	void setInfo(AudioInfo info);
	AudioInfo getInfo();

private:
	std::vector<float> mData;
	AudioInfo mInfo;
};

} // maudio

#endif // MAUDIO_BUFFER


