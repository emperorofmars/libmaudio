/*
 * Interface for manipulating Audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_IMANIPULATOR
#define MAUDIO_IMANIPULATOR

#include "core/audiosource/IAudioSource.hpp"
#include "core/audiosink/IAudioSink.hpp"
#include "core/audiodata/ISample.hpp"
#include "core/audiodata/FileInfo.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <memory>

namespace maudio{

class IManipulator : public IAudioSource{
public:
	virtual ~IManipulator(){};

	virtual void addSource(unsigned int pos, std::shared_ptr<IAudioSource> source) = 0;
	virtual std::shared_ptr<IAudioSource> getSource(unsigned int position) = 0;
	virtual unsigned int getHighestSourcePosition() = 0;
};

} // maudio

#endif // MAUDIO_IMANIPULATOR


