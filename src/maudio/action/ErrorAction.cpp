/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/action/ErrorAction.hpp"

namespace maudio{

ErrorAction::ErrorAction(){
}

ErrorAction::~ErrorAction(){
}

IAudioBuffer *ErrorAction::get(unsigned long pos, unsigned int length) noexcept{
	return NULL;
}

IAudioInfo *ErrorAction::getInfo() noexcept{
	return new AudioInfo();
}

int ErrorAction::MaxInputs() const{
	return -1;
}

bool ErrorAction::HasOutputs() const{
	return true;
}

void ErrorAction::readConfig(const IKeyValueStore *conf){
	return;
}

void ErrorAction::serialize(IMultiLevelStore *data) const{
	data->add("name", getName());
	return;
}

void ErrorAction::deserialize(const IMultiLevelStore *data){
	if(!data) return;
	try{
		setName(data->get("name"));
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

} // maudio



