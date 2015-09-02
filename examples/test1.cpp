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
#include "core/scene/Scene.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;
	
	Scene scene("test_scene");
	long sin1 = scene.add(new SinusGenerator());
	long sin2 = scene.add(new SinusGenerator());
	long mix = scene.add(PluginManager::Instance()->createInstance("Mixer"));
	long play = scene.add(new Player());
	
	scene.connect(sin1, mix);
	scene.connect(sin2, mix);
	scene.connect(mix, play);
	
	auto sin1Prop = scene.get(sin1)->getProperties();
	auto sin1Freq = sin1Prop->getKeyableProperty("Frequency");
	sin1Freq->setKey("500", 0);
	sin1Freq->addKey("500", 0.2);
	sin1Freq->addKey("700", 0.200001);
	sin1Freq->addKey("700", 0.7);
	sin1Freq->addKey("500", 0.700001);
	
	auto sin2Prop = scene.get(sin2)->getProperties();
	auto sin2Freq = sin2Prop->getKeyableProperty("Frequency");
	sin2Freq->setKey("1100", 0);
	
	auto playCtrl = scene.get(play)->getControl();
	
	//scene.disconnect(sin1, mix);
	//scene.disconnect(sin2, mix);
	
	//scene.remove(sin1);
	//scene.remove(sin2);
	
	std::cerr << "play" << std::endl;
	
	playCtrl->callFunction("play");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	playCtrl->callFunction("stop");
	
	std::cerr << "closing main" << std::endl;
	return 0;
}



















