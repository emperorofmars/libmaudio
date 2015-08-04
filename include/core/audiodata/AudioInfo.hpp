/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_AUDIOINFO
#define MAUDIO_AUDIOINFO

#include "core/audiodata/IAudioInfo.hpp"
#include "core/audiodata/FileInfo.hpp"

namespace maudio{

class AudioInfo : public IAudioInfo{
public:
	AudioInfo(){};
	virtual ~AudioInfo(){};

	virtual unsigned long getSamples() const{return mSamples;};
	virtual unsigned long getOffset() const{return mOffset;};
	virtual unsigned int getSamplerate() const{return mSamplerate;};
	virtual unsigned int getChannels() const{return mChannels;};

	virtual void setSamples(unsigned long samples){mSamples = samples;};
	virtual void setOffset(unsigned long offset){mOffset = offset;};
	virtual void setSamplerate(unsigned int samplerate){mSamplerate = samplerate;};
	virtual void setChannels(unsigned int channels){mChannels = channels;};

	virtual void operator=(const IAudioInfo &info){
		setSamples(info.getSamples());
		setOffset(info.getOffset());
		setSamplerate(info.getSamplerate());
		setChannels(info.getChannels());
	}

private:
	unsigned long mSamples;
	unsigned long mOffset;
	unsigned int mSamplerate;
	unsigned int mChannels;
};

} // maudio

#endif // MAUDIO_AUDIOINFO


