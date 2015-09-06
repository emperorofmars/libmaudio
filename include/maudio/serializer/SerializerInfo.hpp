/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SERIALIZERINFO
#define MAUDIO_SERIALIZERINFO

#include "maudio/serializer/ISerializer.hpp"
#include <memory>

namespace maudio{

class SerializerInfo{
public:
	static std::shared_ptr<ISerializer> getSerializer(const char *file);
	static std::shared_ptr<ISerializer> getDefaultSerializer();
};

} // maudio

#endif // MAUDIO_SERIALIZERINFO




