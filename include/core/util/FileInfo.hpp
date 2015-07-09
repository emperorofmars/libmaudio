/*
 * Holds information about a audiostream
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_FILEINFO
#define MAUDIO_FILEINFO

#include <string>
#include "core/util/AudioInfo.hpp"

namespace maudio{

class FileInfo{
public:
	std::string FileName;
	std::string Title;
	std::string Copyright;
	std::string Software;
	std::string Artist;
	std::string Comment;
	std::string Date;
	std::string Album;
	std::string License;
	std::string Tracknumber;
	std::string Genre;
	AudioInfo Info;
};

} // maudio

#endif // MAUDIO_FILEINFO


