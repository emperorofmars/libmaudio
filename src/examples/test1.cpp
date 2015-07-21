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
#include "core/manipulator/Mixer.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	std::shared_ptr<SinusGenerator> sinus1(new SinusGenerator());
	sinus1->setFrequency(500);

	std::shared_ptr<SinusGenerator> sinus2(new SinusGenerator());
	sinus2->setFrequency(1000);

	std::shared_ptr<Mixer> mix(new Mixer());
	mix->addInput(sinus1, 0);
	mix->addInput(sinus2, 1);

	std::shared_ptr<Player> player(new Player());
	player->addInput(mix);

	player->play();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cerr << "stop" << std::endl;
	player->stop();
/*
	std::shared_ptr<TerminalPrinter> printer(new TerminalPrinter());
	printer->addInput(mix);
	for(unsigned int i = 0; i < 50; i++){
		printer->print(i);
	}
*/
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



















