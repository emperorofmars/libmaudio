/*
 * Generates a sinus
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiosource/SinusGenerator.hpp"
#include "core/audiodata/Sample.hpp"
#include "core/util/AudioException.hpp"
#include <cmath>

namespace maudio{

SinusGenerator::SinusGenerator(){
	mFileInfo.Title = "Sinus Test Generator from Maudio";

	mAudioInfo.Channels = 1;
	mAudioInfo.Offset = 0;
	mAudioInfo.Samplerate = 44100;
	mAudioInfo.Samples = 44100;

	mFreq = 1000;
}

SinusGenerator::~SinusGenerator(){
}

void SinusGenerator::setLength(unsigned long samples){
	mAudioInfo.Samples = samples;
}

unsigned long SinusGenerator::getLength(){
	return mAudioInfo.Samples;
}

void SinusGenerator::setFrequency(float freq){
	mFreq = freq;
}

ISample* SinusGenerator::get(unsigned long pos){
	if(pos >= mAudioInfo.Samples + mAudioInfo.Offset || pos < mAudioInfo.Offset) throw OutOfBoundsException();
	ISample *ret = new Sample(mAudioInfo.Channels);
	float index = pos;
	index = fmod(index, 360);
	ret->set(0, sin(mFreq * index * (2 * M_PI) / mAudioInfo.Samplerate));
	return ret;
}

AudioInfo SinusGenerator::getAudioInfo(){
	return mAudioInfo;
}

FileInfo SinusGenerator::getFileInfo(){
	return mFileInfo;
}

} // maudio



