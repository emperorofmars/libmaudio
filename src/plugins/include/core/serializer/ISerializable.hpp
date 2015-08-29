/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ISERIALIZABLE
#define MAUDIO_ISERIALIZABLE

#include "core/store/IMultiLevelStore.hpp"

namespace maudio{

class ISerializable{
public:
	virtual ~ISerializable(){};

	virtual void serialize(IMultiLevelStore *data) const = 0;
	virtual void deserialize(const IMultiLevelStore *data) = 0;
};

} // maudio

#endif // MAUDIO_ISERIALIZABLE




