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
#include "extended/audiosink/Player.hpp"
#include "core/manipulator/Mixer.hpp"
#include "core/manipulator/Resampler.hpp"
#include "core/audiosink/Performance.hpp"
#include "core/property/SimpleProperty.hpp"
#include "core/property/SimpleKeyableProperty.hpp"
#include "core/store/Config.hpp"
#include "core/store/ConfigManager.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	std::shared_ptr<SinusGenerator> sinus1(new SinusGenerator());
	sinus1->setFrequency(500);

	std::shared_ptr<SinusGenerator> sinus2(new SinusGenerator());
	sinus2->setFrequency(1000);

	std::shared_ptr<SinusGenerator> sinus3(new SinusGenerator());
	sinus3->setFrequency(1500);
	sinus3->setSamplerate(22050);

	if(sinus3->getProperties().KeyablePropertyExists("Frequency")){
		std::cerr << "NAME: " << sinus3->getProperties().getKeyableProperty("Frequency")->getName() << std::endl;
		sinus3->getProperties().getKeyableProperty("Frequency")->addKey("2000", 0.5);
	}
	else{
		std::cerr << "FOOOOOOOOOOOOO" << std::endl;
	}

	std::shared_ptr<Resampler> resampler(new Resampler(44100));
	resampler->addInput(sinus3, 0);

	std::shared_ptr<Mixer> mix(new Mixer());
	mix->addInput(sinus1, 0);
	mix->addInput(sinus2, 1);
	mix->addInput(resampler, 2);

	std::shared_ptr<Player> player(new Player());
	player->addInput(mix);
	ConfigManager::Instance()->manipulate().setDefaults();
	//ConfigManager::Instance()->manipulate().set("PlayerQueueSize", 1024);
	player->readConfig(ConfigManager::Instance()->getConfig());

	std::cerr << "play" << std::endl;
	player->play();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//sinus3->setFrequency(1510);
	std::cerr << "half" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cerr << "stop" << std::endl;
	player->stop();


	BoolProperty p("test", false);
	p.set(false);
	std::cerr << p.getName() << " " << p.get() << " " << p.getString() << std::endl;
	p.set("true");
	std::cerr << p.getName() << " " << p.get() << " " << p.getString() << std::endl;

	FloatProperty fp("test", false);
	fp.set(5.68);
	std::cerr << fp.getName() << " " << fp.get() << " " << fp.getString() << std::endl;
	fp.set("34.9");
	std::cerr << fp.getName() << " " << fp.get() << " " << fp.getString() << std::endl;

	KeyableIntProperty ikp("keytest", 5);
	ikp.addKey("625.975", 6.2);
	ikp.addKey(333, 2);
	std::cerr << ikp.getName() << " " << ikp.get(2) << std::endl;
	std::cerr << ikp.getName() << " " << ikp.get(1.8) << std::endl;
	ikp.setKey("222", 0);
	std::cerr << ikp.getName() << " " << ikp.get(0.8) << std::endl;
	std::cerr << ikp.getName() << " " << ikp.get(3.8) << std::endl;
	std::cerr << ikp.getName() << " " << ikp.get(7) << std::endl;

	Config conf;
	try{
		conf.parseFile("maudio.conf");
		std::cerr << "config get: " << conf.get<long>(1) << std::endl;
		std::cerr << "config get: " << conf.get<long>("Stuff") << std::endl;
	}
	catch(std::exception &e){
		std::cerr << "exception" << std::endl;
	}

	ConfigManager::Instance()->getConfig().saveFile("testconfig.txt");

/*
	std::shared_ptr<Performance> perf(new Performance());
	perf->addInput(resampler);

	perf->measure(44100 * 6, 1024 * 10);
	perf->measure(44100 * 6, 1024);
	perf->measure(44100 * 6, 14);
	perf->measure(44100 * 6, 13);
	perf->measure(44100 * 6, 12);
	perf->measure(44100 * 6, 6);
	perf->measure(44100 * 6, 3);
	perf->measure(44100 * 6, 2);
	perf->measure(44100 * 6, 1);
*/
/*
	std::shared_ptr<TerminalPrinter> printer(new TerminalPrinter());
	printer->addInput(mix);
	for(unsigned int i = 0; i < 50; i++){
		printer->print(i);
	}
*/

	std::cerr << "closing main" << std::endl;
	return 0;
}



















