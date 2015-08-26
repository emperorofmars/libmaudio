/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/actions/TerminalPrinter.hpp"
#include "core/util/Util.hpp"
#include "core/util/AudioException.hpp"
#include "core/util/action_ptr.hpp"
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

void TerminalPrinter::readConfig(const IKeyValueStore &conf){
	return;
}

IControl *TerminalPrinter::getControl(){
	return mControl.get();
}

bool TerminalPrinter::checkCompatible(IAudioInfo *info){
	return false;
}

void TerminalPrinter::serialize(IMultiLevelStore *data) const{
	return;
}

void TerminalPrinter::deserialize(const IMultiLevelStore *data){
	return;
}

void TerminalPrinter::print(unsigned long pos){
	if(NumInputs() == 0){
		std::cout << "invalid or no Input" << std::endl;
		return;
	}
	action_ptr<IAudioInfo> tmpInfo(mInputs[0]->getInfo(), mInputs[0]);
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
		action_ptr<ISample> tmpSmp(tmpBuf->get(0), mInputs[0]);
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

unsigned int TerminalPrinter::Control::callFunction(unsigned int num, const char *param){
	if(num == 0){
		mData->print(string_to<unsigned int>(std::string(param)));
		return 0;
	}
	return -1;
}

unsigned int TerminalPrinter::Control::callFunction(const char *name, const char *param){
	if(std::string("print") == std::string(name)){
		mData->print(string_to<unsigned int>(std::string(param)));
		return 0;
	}
	return -1;
}

void TerminalPrinter::Control::stop(){
	return;
}

} // maudio



