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

const unsigned int UniqueID::getID(){
	return mID;
}

const std::string UniqueID::getIDStr(){
	return std::to_string(mID);
}

} // maudio



