/*
 * Testapplication for use when developing
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include <iostream>
#include <chrono>
#include <thread>
#include "core/audiodata/Sample.hpp"
#include "core/audiodata/AudioBuffer.hpp"
#include "core/audiosource/SinusGenerator.hpp"
#include "core/audiosink/TerminalPrinter.hpp"
#include "core/audiosink/Player.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	std::shared_ptr<SinusGenerator> src(new SinusGenerator());
	src->setFrequency(2000);

	std::shared_ptr<Player> dst(new Player());
	dst->addInput(src);

	dst->play();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	dst->stop();

/*
	std::shared_ptr<SinusGenerator> src(new SinusGenerator());
	src->setFrequency(3000);
	std::shared_ptr<INode> cpy = src.get()->shared_from_this();
	src.reset();

	std::shared_ptr<TerminalPrinter> dst(new TerminalPrinter());

	dst->addInput(cpy);

	for(unsigned int i = 0; i < 50; i++){
		dst->print(i);
	}
*/
/*
	Sample s(std::vector<float>{5, 2});
	float x = s[1];
	s[1] = 50;
	x = 10;
	std::cout << s[1] << " " << x << std::endl;

	AudioBuffer b(2, 10);
	b.set(2, s);

	Sample &is = b[2];
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
	sg->setFrequency(3000);
	sg->setLength(45);

	TerminalPrinter *tp = new TerminalPrinter();
	std::shared_ptr<IAudioSink> tpptr(tp);
	tp->setSource(sgptr);

	for(unsigned int i = 0; i < 50; i++){
		tp->print(i);
	}
*/
	return 0;
}



















