/*
 * Testapplication for use when developing
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include <iostream>
#include "core/audiodata/Sample.hpp"
#include "core/audiodata/AudioBuffer.hpp"
#include "core/audiodata/RawSample.hpp"
#include "core/audiodata/RawAudioBuffer.hpp"
#include "core/audiosource/SinusGenerator.hpp"
#include "core/audiosink/TerminalPrinter.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	//Sample s(std::vector<float>{5, 2});
	float arr[] = {5, 2};
	RawSample s(arr, 2);
	float x = s[1];
	s[1] = 50;
	x = 10;
	std::cout << s[1] << " " << x << std::endl;

	RawAudioBuffer b(2, 10);
	b.set(2, s);

	ISample &is = b[2];
	std::cout << is[1] << std::endl;
	std::cout << b[2][1] << std::endl;
	is[1] = 666;
	std::cout << is[1] << std::endl;
	std::cout << b[2][1] << std::endl;

	try{
		std::cout << b[2][0] << std::endl;
		b[2][0] = 42;
		std::cout << b[2][0] << std::endl;
	}
	catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}

	SinusGenerator *sg = new SinusGenerator();
	std::shared_ptr<IAudioSource> sgptr(sg);
	sg->setFrequency(5000);
	sg->setLength(990);
	TerminalPrinter *tp = new TerminalPrinter();
	std::shared_ptr<IAudioSink> tpptr(tp);
	tp->setSource(sgptr);

	for(unsigned int i = 0; i < 1000; i++){
		//std::cout << sg->get(i)->get(0) << std::endl;
		tp->print(i);
	}

	return 0;
}







