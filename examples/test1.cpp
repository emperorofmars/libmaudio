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
/*
#include "extended/audiosink/Player.hpp"
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
#include "core/util/plugin_ptr.hpp"
#include "core/pluginmanager/PluginManager.hpp"
#include "core/util/BaseObserver.hpp"

using namespace maudio;

class ObserverTest : public BaseObserver{
public:
	ObserverTest(){};
	virtual ~ObserverTest(){};

	virtual void notify(const IObservable *origin, NoticeType type, const char *message){
		std::cerr << "notified: " << type << " : ";
		if(message) std::cerr << message << " :";
		std::cerr << std::endl;
	};
};

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	simple_ptr<IKeyValueStore> store1(new KeyValueStore());
	store1->set("stuff", "value1");
	store1->set("bla", "value2");
	store1->set("aaa", "value3");
	std::cerr << store1->get("stuff") << std::endl;
	std::cerr << store1->get("aaa") << std::endl;
	std::cerr << store1->get("bla") << std::endl;
	std::cerr << store1->get((unsigned int)0) << std::endl;

	simple_ptr<IProperty> prop1(new IntProperty("prop1", 678));
	prop1->set("432.567");
	String str(prop1->getString());
	std::cerr << prop1->getName() << " " << prop1->getString() << std::endl;

	std::cerr << "TEST: " << str << std::endl;

	simple_ptr<IKeyableProperty> prop2(new KeyableDoubleProperty("prop2", 1.5));
	prop2->addKey("3", 1);
	std::cerr << prop2->getName() << " " << prop2->getString(0) << std::endl;
	std::cerr << prop2->getName() << " " << prop2->getString(0.1) << std::endl;
	std::cerr << prop2->getName() << " " << prop2->getString(0.5) << std::endl;
	std::cerr << prop2->getName() << " " << prop2->getString(0.75) << std::endl;
	std::cerr << prop2->getName() << " " << prop2->getString(1) << std::endl;

	std::shared_ptr<ActionNode> sgen(new ActionNode(std::unique_ptr<SinusGenerator>(new SinusGenerator())));

	std::shared_ptr<ActionNode> tpr(new ActionNode(std::unique_ptr<TerminalPrinter>(new TerminalPrinter())));
	tpr->addInput(sgen, 0);

	std::cerr << "Sinusgen:" << std::endl;
	simple_ptr<IControl> cntl(tpr->getControl());
	if(cntl){
		cntl->callFunction((unsigned int)0, "123123");
		cntl->callFunction("print", "123124");
	}

	std::cerr << "Plugin:" << std::endl;
/*
	PluginManager::Instance()->addPlugin("plugin.so");
	plugin_ptr<IAction> plug = PluginManager::Instance()->createInstance("TestPlugin");
	IAudioInfo *info = plug->getInfo();
	std::cerr << "Plugintest: " << info->getSamplerate() << std::endl;
	plug->deleteInfo(info);

	std::cerr << "Observer:" << std::endl;

	ObserverTest *obst = new ObserverTest();
	prop2->addObserver(obst);
	prop2->setKey("666", 1);
	prop2->setKey("665", 1);
	delete obst;
	prop2.reset();

*/
	std::cerr << "closing main" << std::endl;
	return 0;
}



















