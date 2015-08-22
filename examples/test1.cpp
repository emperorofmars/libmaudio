/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include <iostream>
#include <chrono>
#include <thread>
#include "core/node/ActionNode.hpp"
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
#include "core/util/String.hpp"
#include "core/util/simple_ptr.hpp"
#include "core/pluginmanager/PluginManager.hpp"
#include "core/util/BaseObserver.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	std::shared_ptr<ActionNode> sgen(new ActionNode(std::unique_ptr<SinusGenerator>(new SinusGenerator())));

	std::shared_ptr<ActionNode> tpr(new ActionNode(std::unique_ptr<TerminalPrinter>(new TerminalPrinter())));
	tpr->addInput(sgen, 0);

	std::cerr << "Sinusgen:" << std::endl;
	IControl *cntl = tpr->getControl();
	if(cntl){
		cntl->callFunction((unsigned int)0, "123123");
		cntl->callFunction("print", "123124");
	}
	IPropertyManager *sinprop = sgen->getProperties();
	if(sinprop){
		IKeyableProperty *freqprop = sinprop->getKeyableProperty("Frequency");
		if(freqprop){
			double mul = 1;

			freqprop->addKey("600", 0 *mul);
			freqprop->addKey("700", 0.5 *mul);
			freqprop->addKey("600", 1 *mul);
			freqprop->addKey("700", 1.5 *mul);
			freqprop->addKey("600", 2 *mul);
			freqprop->addKey("700", 2.5 *mul);
			freqprop->addKey("600", 3 *mul);

			std::cerr << "freqprop: " << std::endl;
			std::cerr << "0: \t" << freqprop->getString(0 *mul) << std::endl;
			std::cerr << "0.25: \t" << freqprop->getString(0.25 *mul) << std::endl;
			std::cerr << "0.5: \t" << freqprop->getString(0.5 *mul) << std::endl;
			std::cerr << "0.75: \t" << freqprop->getString(0.75 *mul) << std::endl;
			std::cerr << "1: \t" << freqprop->getString(1 *mul) << std::endl;
			std::cerr << "1.25: \t" << freqprop->getString(1.25 *mul) << std::endl;
			std::cerr << "1.5: \t" << freqprop->getString(1.5 *mul) << std::endl;
			std::cerr << "1.75: \t" << freqprop->getString(1.75 *mul) << std::endl;
			std::cerr << "2: \t" << freqprop->getString(2 *mul) << std::endl;
			std::cerr << "2.25: \t" << freqprop->getString(2.25 *mul) << std::endl;
		}
	}

	std::cerr << "Plugin:" << std::endl;

	PluginManager::Instance()->addPlugin("plugin.so");
	plugin_ptr<IAction> plug = PluginManager::Instance()->createInstance("TestPlugin");
	action_ptr<IAudioInfo> info(plug->getInfo(), plug.get());
	std::cerr << "Plugintest: " << info->getSamplerate() << std::endl;
	//plug->deleteInfo(info);

	std::cerr << "Player:" << std::endl;

	std::shared_ptr<ActionNode> player(new ActionNode(std::unique_ptr<Player>(new Player())));
	player->addInput(sgen, 0);
	IControl *playerCntl = player->getControl();

	playerCntl->callFunction("play");
	std::this_thread::sleep_for(std::chrono::milliseconds(6000));
	playerCntl->callFunction("stop");

	std::cerr << "closing main" << std::endl;
	return 0;
}



















