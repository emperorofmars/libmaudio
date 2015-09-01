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
#include "core/action/SinusGenerator.hpp"
#include "core/action/TerminalPrinter.hpp"
#include "extended/audiosink/Player.hpp"
/*
#include "core/manipulator/Mixer.hpp"
#include "core/manipulator/Resampler.hpp"
#include "core/audiosink/Performance.hpp"
*/
#include "core/property/SimpleProperty.hpp"
#include "core/property/SimpleKeyableProperty.hpp"
#include "core/store/ConfigManager.hpp"
#include "core/store/MultiStore.hpp"
#include "core/store/MultiLevelStore.hpp"
#include "core/util/String.hpp"
#include "core/pluginmanager/PluginManager.hpp"
#include "core/util/BaseObserver.hpp"
#include "core/util/sptr.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	sptr<IAction> source1(new SinusGenerator());
	IPropertyManager *propm = source1->getProperties();
	IKeyableProperty *propsin = propm->getKeyableProperty("Frequency");
	propsin->setKey("500", 0);
	propsin->addKey("500", 0.2);
	propsin->addKey("700", 0.200001);
	propsin->addKey("700", 0.7);
	propsin->addKey("500", 0.700001);

	sptr<IAction> source2(new SinusGenerator());
	IPropertyManager *propm2 = source2->getProperties();
	IKeyableProperty *propsin2 = propm2->getKeyableProperty("Frequency");
	propsin2->setKey("1100", 0);

	PluginManager::Instance()->addPlugin("./res/plugins/Mixer.so");
	auto mixer = PluginManager::Instance()->createInstance("Mixer");
	if(!mixer->addInput(source1.get(), 0)) std::cerr << "addinput 01 failed" << std::endl;
	if(!mixer->addInput(source2.get(), 1)) std::cerr << "addinput 02 failed" << std::endl;

	sptr<IAction> sink(new Player());
	if(!sink->addInput(mixer.get(), 0)) std::cerr << "addinput 03 failed" << std::endl;
	IControl *sinkCntl = sink->getControl();

	if(!mixer->addInput(sink.get(), 0)) std::cerr << "addinput 04 failed" << std::endl;
	if(!sink->addInput(sink.get(), 0)) std::cerr << "addinput 05 failed" << std::endl;
	if(!source1->addInput(sink.get(), 0)) std::cerr << "addinput 06 failed" << std::endl;
	if(!source1->addInput(source2.get(), 0)) std::cerr << "addinput 07 failed" << std::endl;
	if(!mixer->addInput(mixer.get(), 0)) std::cerr << "addinput 08 failed" << std::endl;

	std::cerr << "source1 ID: " << source1->getID() << std::endl;
	std::cerr << "source2 ID: " << source2->getID() << std::endl;
	std::cerr << "mixer ID: " << mixer->getID() << std::endl;
	std::cerr << "sink ID: " << sink->getID() << std::endl;

	//source1.reset();
	//source2.reset();

	std::cerr << "play" << std::endl;

	sinkCntl->callFunction("play");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	sinkCntl->callFunction("stop");

	std::cerr << "closing main" << std::endl;
	return 0;
}



















