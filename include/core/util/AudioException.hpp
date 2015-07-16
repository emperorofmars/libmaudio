/*
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_OUTOFBOUNDSEXCEPTION
#define MAUDIO_OUTOFBOUNDSEXCEPTION

#include <exception>

namespace maudio{

class OutOfBoundsException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: out of bounds of array of vector!";
	}
};

class ChannelsException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: samples not compatible! (different number of channels)";
	}
};

} // maudio

#endif // MAUDIO_OUTOFBOUNDSEXCEPTION


