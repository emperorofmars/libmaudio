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
#include "core/actions/SinusGenerator.hpp"
/*
#include "core/audiosink/TerminalPrinter.hpp"
#include "extended/audiosink/Player.hpp"
#include "core/manipulator/Mixer.hpp"
#include "core/manipulator/Resampler.hpp"
#include "core/audiosink/Performance.hpp"
*/
#include "core/property/SimpleProperty.hpp"
#include "core/property/SimpleKeyableProperty.hpp"
#include "core/store/Config.hpp"
#include "core/store/ConfigManager.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	IKeyValueStore *store1 = new KeyValueStore();
	store1->set("stuff", "value1");
	store1->set("bla", "value2");
	store1->set("aaa", "value3");
	std::cerr << store1->get("stuff") << std::endl;
	std::cerr << store1->get("aaa") << std::endl;
	std::cerr << store1->get("bla") << std::endl;
	std::cerr << store1->get((unsigned int)0) << std::endl;
	delete store1;

	IProperty *prop1 = new IntProperty("prop1", 678);
	prop1->set("432.567");
	std::cerr << prop1->getName() << " " << prop1->getString() << std::endl;
	delete prop1;

	IKeyableProperty *prop2 = new KeyableDoubleProperty("prop2", 1.5);
	prop2->addKey("3", 1);
	std::cerr << prop2->getName() << " " << prop2->getString(0) << std::endl;
	std::cerr << prop2->getName() << " " << prop2->getString(0.1) << std::endl;
	std::cerr << prop2->getName() << " " << prop2->getString(0.5) << std::endl;
	std::cerr << prop2->getName() << " " << prop2->getString(0.75) << std::endl;
	std::cerr << prop2->getName() << " " << prop2->getString(1) << std::endl;
	delete prop2;

	SinusGenerator gen;
	IAudioBuffer *buf;
	ISample *smp;
	buf = gen.get(2423, 1);
	smp = buf->get(0);
	std::cerr << smp->get(0) << std::endl;
	delete smp;
	delete buf;

	std::cerr << "closing main" << std::endl;
	return 0;
}



















