/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/audiodata/AudioInfo.hpp"
#include "maudio/util/Util.hpp"
#include <string>

namespace maudio{

void AudioInfo::operator=(const IAudioInfo &info){
	setSamples(info.getSamples());
	setOffset(info.getOffset());
	setSamplerate(info.getSamplerate());
	setChannels(info.getChannels());
}

void AudioInfo::serialize(IMultiLevelStore *data) const{
	if(!data) return;
	data->add("samples", std::to_string(mSamples).c_str());
	data->add("offset", std::to_string(mOffset).c_str());
	data->add("samplerate", std::to_string(mSamplerate).c_str());
	data->add("channels", std::to_string(mChannels).c_str());
	return;
}

void AudioInfo::deserialize(const IMultiLevelStore *data){
	if(!data) return;
	try{
		mSamples = string_to<unsigned long>(std::string(data->get("samples")));
		mOffset = string_to<unsigned long>(std::string(data->get("offset")));
		mSamplerate = string_to<unsigned int>(std::string(data->get("samplerate")));
		mChannels = string_to<unsigned int>(std::string(data->get("channels")));
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

} // maudio



