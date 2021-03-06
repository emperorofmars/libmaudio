/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_FILEINFO
#define MAUDIO_FILEINFO

#include <string>

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
};

} // maudio

#endif // MAUDIO_FILEINFO


