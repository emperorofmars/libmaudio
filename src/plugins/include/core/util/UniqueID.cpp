/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/util/UniqueID.hpp"

namespace maudio{

unsigned int UniqueID::mGlobalID = 0;

UniqueID::UniqueID(){
	mGlobalID++;
	mID = mGlobalID;
}

unsigned int UniqueID::getID() const{
	return mID;
}

std::string UniqueID::getIDStr() const{
	return std::to_string(mID);
}

} // maudio



