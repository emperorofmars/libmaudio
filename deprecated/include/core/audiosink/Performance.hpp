/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PERFORMANCE
#define MAUDIO_PERFORMANCE

#include "core/audiosink/BaseAudioSink.hpp"

namespace maudio{

class Performance : public BaseAudioSink{
public:
	Performance();
	virtual ~Performance();

	virtual AudioInfo getInfo() noexcept;
	virtual void readConfig(const Config &conf);

	void measure(unsigned long length, unsigned int buflen);
};

} // maudio

#endif // MAUDIO_PERFORMANCE


