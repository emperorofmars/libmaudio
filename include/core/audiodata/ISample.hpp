/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ISAMPLE
#define MAUDIO_ISAMPLE

namespace maudio{

///Holds a sample of audio
class ISample{
public:
	virtual ~ISample(){};

	virtual const float operator[](unsigned int pos) const = 0;
	virtual float get(unsigned int pos) const = 0;
	virtual void set(float data, unsigned int pos) = 0;
	virtual unsigned int getChannels() const = 0;

	virtual ISample *operator+(const ISample &data) = 0;
	virtual ISample *operator-(const ISample &data) = 0;
	virtual ISample *operator*(const ISample &data) = 0;
	virtual ISample *operator/(const ISample &data) = 0;

	virtual ISample *operator*(float data) = 0;
	virtual ISample *operator/(float data) = 0;

	virtual void operator+=(const ISample &data) = 0;
	virtual void operator-=(const ISample &data) = 0;
	virtual void operator*=(const ISample &data) = 0;
	virtual void operator/=(const ISample &data) = 0;

	virtual void operator*=(float data) = 0;
	virtual void operator/=(float data) = 0;
};

} // maudio

#endif // MAUDIO_ISAMPLE


