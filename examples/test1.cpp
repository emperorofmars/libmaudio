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
			double mul = 0.83;
			double shift = 0.11;
/*
			freqprop->setKey("600", 0);
			freqprop->addKey("600", 0 *mul+shift);
			freqprop->addKey("700", 1 *mul+shift);
			freqprop->addKey("600", 2 *mul+shift);
			freqprop->addKey("600", 3 *mul+shift);
			freqprop->addKey("700", 3.5 *mul+shift);
			freqprop->addKey("600", 4 *mul+shift);
			freqprop->addKey("700", 4.5 *mul+shift);
*/

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

/*
			freqprop->setKey("600", 0);
			freqprop->addKey("1000", 1);
			freqprop->addKey("1400", 1.001);
			freqprop->addKey("1400", 2);
*/
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

		MultiLevelStore serializerStore1;
		MultiLevelStore serializerStore2;
		IProperty *sinsmpprop = sinprop->getProperty("Samplerate");
		if(sinsmpprop){
			sinsmpprop->serialize(&serializerStore1);

			SimpleProperty<unsigned int> smpprop("asdas", 1);
			smpprop.deserialize(&serializerStore1);
			std::cerr << "Deserialize: " << smpprop.getName() << " " << smpprop.get() << std::endl;
		}
		if(freqprop){
			freqprop->serialize(&serializerStore2);
			std::cerr << "freqprop: " << serializerStore2.get("value", 0) << std::endl;
			std::cerr << "freqprop: " << serializerStore2.get("value", 1) << std::endl;
			std::cerr << "freqprop: " << serializerStore2.get("value", 2) << std::endl;
			std::cerr << "freqprop: " << serializerStore2.get("value", 3) << std::endl;

			KeyableFloatProperty desfreq("fuu", 0);
			desfreq.deserialize(&serializerStore2);
			std::cerr << "Deserialize: " << desfreq.getName() << " " << desfreq.get(2.3) << std::endl;

		}
	}
	std::cerr << "MultiMap:" << std::endl;

	try{
		MultiLevelStore mstore;
		mstore.add("plugin", "foo");
		mstore.add("plugin", "bar");
		mstore.add("plugin", "blah");
		mstore.add("info", 234);
		std::cerr << mstore.get("plugin", 0) << std::endl;
		std::cerr << mstore.get("plugin", 2) << std::endl;
		std::cerr << mstore.get("plugin", 1) << std::endl;
		std::cerr << mstore.get((unsigned int)0, 0) << std::endl;
		mstore.addLevel("bla");
		auto storelevel = mstore.getLevel("bla");
		storelevel->add("bla", "123");
		storelevel->add("bla", "654654654");
		std::cerr << storelevel->get("bla") << std::endl;
		std::cerr << storelevel->get("bla", 1) << std::endl;
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
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



















