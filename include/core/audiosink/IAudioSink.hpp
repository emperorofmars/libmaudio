/*
 * Interface for releasing audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_IAUDIOSINK
#define MAUDIO_IAUDIOSINK

#include "core/audiosource/IAudioSource.hpp"
#include <memory>

namespace maudio{

class IAudioSink{
public:
	virtual ~IAudioSink(){};

	virtual void setSource(std::weak_ptr<IAudioSource> source) = 0;
	virtual std::shared_ptr<IAudioSource> getSource() = 0;

    virtual AudioInfo getAudioInfo() = 0;
    virtual FileInfo getFileInfo() = 0;
};

} // maudio

#endif // MAUDIO_IAUDIOSINK


