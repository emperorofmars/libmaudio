/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SERIALIZERSTORE
#define MAUDIO_SERIALIZERSTORE

#include "core/store/KeyValueStore.hpp"

namespace maudio{

class SerializerStore : public KeyValueStore{
public:
	SerializerStore();
	virtual ~SerializerStore();

	//add SerializerStore

};

} // maudio

#endif // MAUDIO_SERIALIZERSTORE









