/*
 * Holds information about a audiostream
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_AUDIOINFO
#define MAUDIO_AUDIOINFO

namespace maudio{

class AudioInfo{
public:
	unsigned long Samples;
	unsigned long Offset;
	unsigned int Samplerate;
	unsigned int Channels;
};

} // maudio

#endif // MAUDIO_AUDIOINFO


