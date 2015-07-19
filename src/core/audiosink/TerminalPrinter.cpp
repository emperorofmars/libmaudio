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
	/*
	if(mNodes.size() < 1 || !mNodes[0]){
		std::cout << "no Node" << std::endl;
		return;
	}
	try{
		for(unsigned int i = 0; i < mNodes[0]->getAudioInfo().Channels; i++){
			std::cout << mNodes[0]->get(pos, 0).get(i) << " ";
		}
	}
	catch(OutOfBoundsException &e){
		std::cout << "Out of Bounds";
	}
	catch(...){
		std::cout << "An Exception occurred";
	}
	std::cout << std::endl;
	*/
}

} // maudio



