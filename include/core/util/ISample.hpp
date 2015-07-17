/*
 * Holds a single sample of audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_ISAMPLE
#define MAUDIO_ISAMPLE

namespace maudio{

///holds a frame of audio
class ISample{
public:
	virtual ~ISample(){};

	virtual float& operator[](unsigned int pos) = 0;
	virtual void operator=(ISample &data) = 0;
	virtual float get(unsigned int pos) = 0;
	virtual void set(float data, unsigned int pos) = 0;
	virtual unsigned int getChannels() = 0;
};

} // maudio

#endif // MAUDIO_ISAMPLE


