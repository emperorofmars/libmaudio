/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_UTIL
#define MAUDIO_UTIL

#include <string>

namespace maudio{

double PositionToSeconds(unsigned long pos, unsigned int samplerate);
unsigned long SecondsToPosition(double pos, unsigned int samplerate);

template<typename T>
T string_to(const std::string &str);

} // maudio

#endif // MAUDIO_UTIL




