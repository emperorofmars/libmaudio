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

sptr<IAction> TypeManager::create(const char *type){
	sptr<IAction> ret;
	try{
		ret = PluginManager::Instance()->createInstance(type);
		if(ret) return ret;
	}
	catch(std::exception &e){
		
	}
	std::string mtype(type);
	
	if(mtype == "SinusGenerator"){
		ret.reset(new SinusGenerator());
		return ret;
	}
	if(mtype == "TerminalPrinter"){
		ret.reset(new TerminalPrinter());
		return ret;
	}
	if(mtype == "Player"){
		ret.reset(new Player());
		return ret;
	}
	return NULL;
}

} // maudio



