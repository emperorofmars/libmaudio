/*
 * Generates a sinus
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiosource/SinusGenerator.hpp"
#include "core/util/AudioException.hpp"
#include <cmath>

namespace maudio{

SinusGenerator::SinusGenerator(){
	mAudioInfo.mFileInfo.Title = "Sinus Test Generator from Maudio";

	mAudioInfo.Channels = 1;
	mAudioInfo.Offset = 0;
	mAudioInfo.Samplerate = 44100;
	mAudioInfo.Samples = 44100;

	mFreq = 1000;
}

SinusGenerator::~SinusGenerator(){
}

void SinusGenerator::setFrequency(float freq){
	mFreq = freq;
}

Sample SinusGenerator::get(unsigned long pos){
	Sample ret(mAudioInfo.Channels);
	float index = pos;
	ret.set(0, sin(mFreq * index * (2 * M_PI) / mAudioInfo.Samplerate));
	return ret;
}

AudioInfo SinusGenerator::getAudioInfo(){
	return mAudioInfo;
}

} // maudio



