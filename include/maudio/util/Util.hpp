/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_UTIL
#define MAUDIO_UTIL

#include <string>
#include <vector>

namespace maudio{

double PositionToSeconds(unsigned long pos, unsigned int samplerate);
unsigned long SecondsToPosition(double pos, unsigned int samplerate);

template<typename T>
T string_to(const std::string &str);

const char* to_chararray(bool value);
const char* to_chararray(int value);
const char* to_chararray(unsigned int value);
const char* to_chararray(long value);
const char* to_chararray(unsigned long value);
const char* to_chararray(float value);
const char* to_chararray(double value);
const char* to_chararray(long double value);
const char* to_chararray(const char *value);
const char* to_chararray(std::string &value);
const char* to_chararray(std::string value);

std::vector<std::string> split(const std::string &str, char delim = ' ');

} // maudio

#endif // MAUDIO_UTIL




