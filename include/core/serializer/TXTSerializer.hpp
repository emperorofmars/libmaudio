/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_TXTSERIALIZER
#define MAUDIO_TXTSERIALIZER

#include "core/serializer/ISerializer.hpp"

namespace maudio{

class TXTSerializer : public ISerializer{
public:
	TXTSerializer();
	~TXTSerializer();

	//load and save scene
};

} // maudio

#endif // MAUDIO_TXTSERIALIZER




