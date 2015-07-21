/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
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
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cerr << "stop" << std::endl;
	dst->stop();

/*
	std::shared_ptr<SinusGenerator> src(new SinusGenerator());
	src->setFrequency(3000);
	std::shared_ptr<Node> cpy = src.get()->shared_from_this();
	src.reset();

	std::shared_ptr<TerminalPrinter> dst(new TerminalPrinter());

	dst->addInput(cpy);

	for(unsigned int i = 0; i < 50; i++){
		dst->print(i);
	}
*/
	std::cerr << "closing main" << std::endl;
	return 0;
}



















