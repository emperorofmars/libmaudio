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
#include "core/serializer/TXTSerializer.hpp"
/*
#include "core/manipulator/Mixer.hpp"
#include "core/manipulator/Resampler.hpp"
#include "core/audiosink/Performance.hpp"
*/

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;
	
	std::shared_ptr<Scene> scene1(new Scene("test_scene"));
	long sin1 = scene1->add(TypeManager::create("SinusGenerator", "sin1"));
	long sin2 = scene1->add(TypeManager::create("SinusGenerator", "sin2"));
	long mix = scene1->add(TypeManager::create("Mixer", "mix"));
	long play = scene1->add(TypeManager::create("Player", "play"));
	
	scene1->connect(sin1, mix);
	scene1->connect(sin2, mix);
	scene1->connect(mix, play);
	
	auto sin1Prop = scene1->get(sin1)->getProperties();
	auto sin1Freq = sin1Prop->getKeyableProperty("Frequency");
	sin1Freq->setKey("500", 0);
	sin1Freq->addKey("500", 0.2);
	sin1Freq->addKey("700", 0.200001);
	sin1Freq->addKey("700", 0.7);
	sin1Freq->addKey("500", 0.700001);
	
	/*
	MultiLevelStore mstore;
	sin1Freq->serialize(&mstore);
	std::cerr << "mstore: " << mstore.getSize() << std::endl;
	for(unsigned int i = 0; i < mstore.getSize(); i++){
		std::cerr << mstore.getKey(i) << " " << mstore.get(i) << std::endl;
	}
	*/
	
	auto sin2Prop = scene1->get(sin2)->getProperties();
	auto sin2Freq = sin2Prop->getKeyableProperty("Frequency");
	sin2Freq->setKey("1100", 0);
	
	std::cerr << "serialize" << std::endl;
	
	IMultiLevelStore *sceneStore = new MultiLevelStore();
	scene1->serialize(sceneStore);
	
	std::cerr << "deserialize" << std::endl;
	
	std::shared_ptr<Scene> scene2(new Scene("serialize_test"));
	try{
		scene2->deserialize(sceneStore);
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
	}
	
	auto playCtrl2 = scene2->get(scene2->getEnd(0)->getID())->getControl();
	
	std::cerr << "play" << std::endl;
	
	playCtrl2->callFunction("play");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	playCtrl2->callFunction("stop");
	
	TXTSerializer serializer;
	serializer.addScene(scene1);
	serializer.writeFile("testfile.maup");
	
	std::cerr << "closing main" << std::endl;
	return 0;
}



















