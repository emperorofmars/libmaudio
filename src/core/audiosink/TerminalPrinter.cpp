/*
 * Generates a sinus
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiosink/TerminalPrinter.hpp"
#include "core/util/AudioException.hpp"
#include <iostream>

namespace maudio{

TerminalPrinter::TerminalPrinter(){
}

TerminalPrinter::~TerminalPrinter(){
}

void TerminalPrinter::print(unsigned long pos) const{
	/*if(mInputs.size() < 1 || !mInputs[0] || !mInputs[0]->valid()){
		std::cout << "invalid or no Input" << std::endl;
		return;
	}
	try{
		for(unsigned int i = 0; i < mInputs[0]->getInput()->getAudioInfo().Channels; i++){
			std::cout << mInputs[0]->getInput()->get(pos).get(i) << " ";
		}
	}
	catch(OutOfBoundsException &e){
		std::cout << "Out of Bounds";
	}
	catch(...){
		std::cout << "An Exception occurred";
	}
	std::cout << std::endl;*/
}

} // maudio



