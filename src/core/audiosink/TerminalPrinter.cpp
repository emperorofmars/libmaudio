/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiosink/TerminalPrinter.hpp"
#include "core/util/AudioException.hpp"
#include <iostream>

namespace maudio{

TerminalPrinter::TerminalPrinter(){
}

TerminalPrinter::~TerminalPrinter(){
}

AudioInfo TerminalPrinter::getInfo() noexcept{
	AudioInfo ret;
	if(NumInputs() > 0) return getInfoFromSlot(0);
	return ret;
}

void TerminalPrinter::print(unsigned long pos){
	if(NumInputs() == 0){
		std::cout << "invalid or no Input" << std::endl;
		return;
	}
	for(unsigned int i = 0; i < getInfoFromSlot(0).Channels; i++){
		std::cout << getFromSlot(pos, 1, 0).get(0).get(i) << " ";
	}
	std::cout << std::endl;
	return;
}

} // maudio



