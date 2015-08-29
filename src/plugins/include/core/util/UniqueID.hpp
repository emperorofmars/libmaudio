/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */


#ifndef MAUDIO_ID
#define MAUDIO_ID

#include <string>

namespace maudio{

class UniqueID{
public:
	UniqueID();
	unsigned int getID() const;
	std::string getIDStr() const;

private:
	unsigned int mID;
	static unsigned int mGlobalID;
};

} // maudio

#endif // MAUDIO_ID









