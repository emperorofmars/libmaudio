/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/scene/TypeManager.hpp"
#include "core/pluginmanager/PluginManager.hpp"
#include "core/action/ErrorAction.hpp"
#include "core/action/SinusGenerator.hpp"
#include "core/action/TerminalPrinter.hpp"
#include "extended/audiosink/Player.hpp"
#include <string>

namespace maudio{

sptr<IAction> TypeManager::create(const char *type, const char *name){
	sptr<IAction> ret;
	std::string mtype(type);
	
	if(mtype == "SinusGenerator"){
		ret.reset(new SinusGenerator());
	}
	else if(mtype == "TerminalPrinter"){
		ret.reset(new TerminalPrinter());
	}
	else if(mtype == "Player"){
		ret.reset(new Player());
	}
	else if(mtype == "ErrorAction"){
		ret.reset(new ErrorAction());
	}
	if(!ret){
		try{
			ret = PluginManager::Instance()->createInstance(type);
		}
		catch(std::exception &e){
			
		}
	}
	if(ret && name){
		ret->setName(name);
	}
	if(!ret){
		ret.reset(new ErrorAction());
		if(name){
			ret->setName(name);
		}
	}
	return ret;
}

} // maudio



