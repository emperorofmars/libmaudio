/*
 * class to get unique IDs
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_ID
#define MAUDIO_ID

#include <string>

namespace maudio{

class UniqueID{
public:
	UniqueID();
	const unsigned int getID();
	const std::string getIDStr();

private:
	unsigned int mID;
	static unsigned int mGlobalID;
};

} // maudio

#endif // MAUDIO_ID









