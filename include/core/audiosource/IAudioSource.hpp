/*
 * Interface for getting Audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_IAUDIOSOURCE
#define MAUDIO_IAUDIOSOURCE

#include "core/audiodata/ISample.hpp"
#include "core/audiodata/FileInfo.hpp"
#include "core/audiodata/AudioInfo.hpp"

namespace maudio{

class IAudioSource{
public:
	virtual ~IAudioSource(){};

    virtual ISample* get(unsigned long pos) = 0;
    virtual AudioInfo getAudioInfo() = 0;
    virtual FileInfo getFileInfo() = 0;
};

} // maudio

#endif // MAUDIO_IAUDIOSOURCE


