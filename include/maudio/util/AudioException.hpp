/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */


#ifndef MAUDIO_EXCEPTION
#define MAUDIO_EXCEPTION

#include <exception>
#include <string>

namespace maudio{

class MaudioException : public std::exception{
public:
	MaudioException(std::string &info){mInfo = "maudio: " + info;}
	MaudioException(const char *info){mInfo = "maudio: "; mInfo.append(info);}
	virtual const char* what() const throw(){
		return mInfo.c_str();
	}
private:
	std::string mInfo;
};

class OutOfBoundsException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: out of bounds of array of vector";
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

class CircleException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: attempting to create cycle in an acyclic graph";
	}
};

class PlayerException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: could not open audio output stream";
	}
};

class InvalidDataException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: received invalid data";
	}
};

class InternalException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: an error occurred";
	}
};

class InvalidAudioDeviceException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "maudio: attempting to open an invalid audiodevice";
	}
};

} // maudio

#endif // MAUDIO_EXCEPTION


