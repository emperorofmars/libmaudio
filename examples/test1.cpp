/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include <iostream>
#include <chrono>
#include <thread>
#include "core/action/SinusGenerator.hpp"
#include "core/action/TerminalPrinter.hpp"
#include "extended/audiosink/Player.hpp"
#include "core/store/ConfigManager.hpp"
#include "core/pluginmanager/PluginManager.hpp"
#include "core/scene/Scene.hpp"
#include "core/scene/TypeManager.hpp"
#include "core/store/MultiLevelStore.hpp"
/*
#include "core/manipulator/Mixer.hpp"
#include "core/manipulator/Resampler.hpp"
#include "core/audiosink/Performance.hpp"
*/

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;
	
	Scene scene("test_scene");
	long sin1 = scene.add(TypeManager::create("SinusGenerator"));
	long sin2 = scene.add(TypeManager::create("SinusGenerator"));
	long mix = scene.add(TypeManager::create("Mixer"));
	long play = scene.add(TypeManager::create("Player"));
	
	scene.get(sin1)->setName("sin1");
	scene.get(sin2)->setName("sin2");
	scene.get(mix)->setName("mix");
	scene.get(play)->setName("play");
	
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
	
	std::cerr << "scene: " << scene.getName() << " :: ends: " << scene.getNumEnds() << std::endl;
	
	auto sink01 = scene.getEnd(0);
	if(sink01){
		std::cerr << "sink01 ID: " << sink01->getID() << std::endl;
		std::cerr << "sink01 Name: " << sink01->getName() << std::endl;
	}
	
	/*
	auto playCtrl = scene.get(play)->getControl();
	
	//scene.disconnect(sin1, mix);
	//scene.disconnect(sin2, mix);
	
	//scene.remove(sin1);
	//scene.remove(sin2);
	
	std::cerr << "play" << std::endl;
	
	playCtrl->callFunction("play");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	playCtrl->callFunction("stop");
	*/
	
	std::cerr << "serialize" << std::endl;
	
	IMultiLevelStore *sceneStore = new MultiLevelStore();
	scene.serialize(sceneStore);
	
	std::cerr << "deserialize" << std::endl;
	
	Scene scene2("serialize_test");
	try{
		scene2.deserialize(sceneStore);
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
	}
	
	std::cerr << "scene2: " << scene2.getName() << " :: ends: " << scene2.getNumEnds() << std::endl;
	
	auto sink02 = scene2.getEnd(0);
	if(sink02){
		std::cerr << "sink02 ID: " << sink02->getID() << std::endl;
		std::cerr << "sink02 Name: " << sink02->getName() << std::endl;
		std::cerr << "sink02 Inputs: " << sink02->NumInputs() << std::endl;
	}
	else{
		std::cerr << "sink02 fail!" << std::endl;
	}
	
	std::cerr << "closing main" << std::endl;
	return 0;
}



















