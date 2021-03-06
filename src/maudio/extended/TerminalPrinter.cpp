/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/extended/TerminalPrinter.hpp"
#include "maudio/util/Util.hpp"
#include "maudio/util/AudioException.hpp"
#include "maudio/util/sptr.hpp"
#include <iostream>
#include <cstring>

namespace maudio{

TerminalPrinter::TerminalPrinter(){
}

TerminalPrinter::~TerminalPrinter(){
}

IAudioBuffer *TerminalPrinter::get(unsigned long pos, unsigned int length) noexcept{
	return NULL;
}

IAudioInfo *TerminalPrinter::getInfo() noexcept{
	return NULL;
}

int TerminalPrinter::MaxInputs() const{
	return 1;
}

bool TerminalPrinter::HasOutputs() const{
	return false;
}

void TerminalPrinter::readConfig(const IKeyValueStore *conf){
	return;
}

IControl *TerminalPrinter::getControl(){
	return mControl.get();
}

bool TerminalPrinter::checkCompatible(IAudioInfo *info){
	return false;
}

void TerminalPrinter::serialize(IMultiLevelStore *data) const{
	if(!data) return;
	data->add("name", getName());
	return;
}

void TerminalPrinter::deserialize(const IMultiLevelStore *data){
	if(!data) return;
	try{
		setName(data->get("name"));
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

void TerminalPrinter::print(unsigned long pos){
	if(NumInputs() == 0){
		std::cout << "invalid or no Input" << std::endl;
		return;
	}
	auto tmpInfo = getInfoFromSlot(0);
	if(!tmpInfo){
		std::cout << "failed retrieving info" << std::endl;
		return;
	}
	for(unsigned int i = 0; i < tmpInfo->getChannels(); i++){
		auto tmpBuf = getFromSlot(0, pos, 1);
		if(!tmpBuf){
			std::cout << "failed retrieving buffer" << std::endl;
			return;
		}
		auto tmpSmp = getSampleFromBuffer(0, tmpBuf);
		if(!tmpSmp){
			std::cout << "failed retrieving sample" << std::endl;
			return;
		}
		std::cout << tmpSmp->get(i) << " ";
	}
	std::cout << std::endl;
	return;
}


TerminalPrinter::Control::Control(TerminalPrinter *data){
	mData = data;
}

TerminalPrinter::Control::~Control(){
}

unsigned int TerminalPrinter::Control::getNumFunctions(){
	return 1;
}

const char *TerminalPrinter::Control::getFunctionName(unsigned int num){
	if(num == 0) return "print";
	return NULL;
}

const char *TerminalPrinter::Control::getFunctionParam(unsigned int num){
	if(num == 0) return "int:pos;";
	return NULL;
}

const char *TerminalPrinter::Control::callFunction(unsigned int num, const char *param){
	if(num == 0){
		mData->print(string_to<unsigned int>(std::string(param)));
		return NULL;
	}
	return NULL;
}

const char *TerminalPrinter::Control::callFunction(const char *name, const char *param){
	if(std::string("print") == std::string(name)){
		mData->print(string_to<unsigned int>(std::string(param)));
		return NULL;
	}
	return NULL;
}

void TerminalPrinter::Control::stop(){
	return;
}

} // maudio



