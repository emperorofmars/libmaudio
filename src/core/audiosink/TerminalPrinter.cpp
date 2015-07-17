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

void TerminalPrinter::setSource(std::shared_ptr<IAudioSource> source){
	mSource = source;
}

std::shared_ptr<IAudioSource> TerminalPrinter::getSource(){
	return mSource.lock();
}

void TerminalPrinter::print(unsigned long pos){
	std::shared_ptr<IAudioSource> tmp = mSource.lock();
	if(!tmp) return;
	try{
		for(unsigned int i = 0; i < tmp->getAudioInfo().Channels; i++){
			std::cout << tmp->get(pos)->get(i) << " ";
		}
	}
	catch(OutOfBoundsException &e){
		std::cout << "Out of Bounds";
	}
	catch(...){
		std::cout << "An Exception occurred";
	}
	std::cout << std::endl;
}

} // maudio



