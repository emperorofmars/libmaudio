/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ISERIALIZER
#define MAUDIO_ISERIALIZER

#include "core/scene/Scene.hpp"
#include "core/serializer/ISerializable.hpp"
#include "core/store/IMultiLevelStore.hpp"

namespace maudio{

class ISerializer{
public:
	virtual ~ISerializer(){};

	virtual void add(Scene *data) = 0;
	virtual Scene *getScene(const char *name) = 0;
	virtual Scene *getScene(unsigned int i) = 0;

	virtual IMultiLevelStore *getStore() = 0;

	virtual void write(const char *path) = 0;
	virtual void parse(const char *path) = 0;
};

} // maudio

#endif // MAUDIO_ISERIALIZER




