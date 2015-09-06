/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */


#ifndef MAUDIO_UNIQUEID
#define MAUDIO_UNIQUEID

#include <string>

namespace maudio{

class UniqueID{
public:
	UniqueID();
	unsigned long getID() const;
	std::string getIDStr() const;

private:
	unsigned long mID;
	static unsigned long mGlobalID;
};

} // maudio

#endif // MAUDIO_UNIQUEID









