/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/scene/TypeManager.hpp"
#include "core/pluginmanager/PluginManager.hpp"
#include "core/action/SinusGenerator.hpp"
#include "core/action/TerminalPrinter.hpp"
#include "extended/audiosink/Player.hpp"
#include <string>

namespace maudio{

sptr<IAction> TypeManager::create(const char *type, const char *name){
	sptr<IAction> ret;
	try{
		ret = PluginManager::Instance()->createInstance(type);
	}
	catch(std::exception &e){
		
	}
	std::string mtype(type);
	if(!ret){
		if(mtype == "SinusGenerator"){
			ret.reset(new SinusGenerator());
		}
		else if(mtype == "TerminalPrinter"){
			ret.reset(new TerminalPrinter());
		}
		else if(mtype == "Player"){
			ret.reset(new Player());
		}
	}
	if(ret && name){
		ret->setName(name);
	}
	return ret;
}

} // maudio



