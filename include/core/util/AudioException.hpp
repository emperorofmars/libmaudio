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

class BadOutputException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: accessing non existing output index";
	}
};

class BadInputException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: accessing non existing input index";
	}
};

} // maudio

#endif // MAUDIO_OUTOFBOUNDSEXCEPTION


