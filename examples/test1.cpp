/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include <iostream>
#include <chrono>
#include <thread>
#include "core/node/ActionNode.hpp"
#include "core/node/PluginNode.hpp"
#include "core/audiodata/Sample.hpp"
#include "core/audiodata/AudioBuffer.hpp"
#include "core/actions/SinusGenerator.hpp"
#include "core/actions/TerminalPrinter.hpp"
#include "extended/audiosink/Player.hpp"
/*
#include "core/manipulator/Mixer.hpp"
#include "core/manipulator/Resampler.hpp"
#include "core/audiosink/Performance.hpp"
*/
#include "core/property/SimpleProperty.hpp"
#include "core/property/SimpleKeyableProperty.hpp"
#include "core/store/Config.hpp"
#include "core/store/ConfigManager.hpp"
#include "core/store/MultiStore.hpp"
#include "core/store/MultiLevelStore.hpp"
#include "core/util/String.hpp"
#include "core/util/simple_ptr.hpp"
#include "core/pluginmanager/PluginManager.hpp"
#include "core/util/BaseObserver.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	std::shared_ptr<ActionNode> sgen(new ActionNode(std::unique_ptr<SinusGenerator>(new SinusGenerator())));
	std::shared_ptr<ActionNode> sgen2(new ActionNode(std::unique_ptr<SinusGenerator>(new SinusGenerator())));

	IPropertyManager *sinprop = sgen->getProperties();
	if(sinprop){
		IKeyableProperty *freqprop = sinprop->getKeyableProperty("Frequency");
		if(freqprop){
			double mul = 0.83;
			double shift = 0.11;

			freqprop->setKey("600", 0);
			freqprop->addKey("600", 0 *mul+shift);
			freqprop->addKey("900", 0.000001 *mul+shift);
			freqprop->addKey("900", 1 *mul+shift);
			freqprop->addKey("600", 1.000001 *mul+shift);
			freqprop->addKey("600", 2 *mul+shift);
			freqprop->addKey("900", 2.000001 *mul+shift);
			freqprop->addKey("900", 3 *mul+shift);
			freqprop->addKey("600", 3.000001 *mul+shift);
			freqprop->addKey("600", 4 *mul+shift);
			freqprop->addKey("900", 4.000001 *mul+shift);
			freqprop->addKey("900", 5 *mul+shift);
			freqprop->addKey("600", 5.000001 *mul+shift);
		}
	}

	std::cerr << "Plugin:" << std::endl;

	PluginManager::Instance()->addPlugin("./Mixer.so");
	std::shared_ptr<PluginNode> mix(new PluginNode(PluginManager::Instance()->createInstance("Mixer")));

	mix->addInput(sgen, 0);
	mix->addInput(sgen2, 1);

	std::cerr << "Plugin Inputs: " << mix->NumInputs() << std::endl;

	action_ptr<IAudioInfo> info(mix->getInfo(), mix.get());
	if(info){
		std::cerr << "Plugin Info: " << info->getSamplerate() << std::endl;
	}
	else{
		std::cerr << "Plugin Fail" << std::endl;
	}

	std::cerr << "Player:" << std::endl;

	std::shared_ptr<ActionNode> player(new ActionNode(std::unique_ptr<Player>(new Player())));
	player->addInput(mix, 0);
	IControl *playerCntl = player->getControl();

	playerCntl->callFunction("play");
	std::this_thread::sleep_for(std::chrono::milliseconds(6000));
	playerCntl->callFunction("stop");

	std::cerr << "closing main" << std::endl;
	return 0;
}



















