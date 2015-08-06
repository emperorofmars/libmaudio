/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IACTION
#define MAUDIO_IACTION

#include "core/node/ISocket.hpp"
#include "core/audiodata/IAudioBuffer.hpp"
#include "core/audiodata/IAudioInfo.hpp"
#include "core/property/Property.hpp"
#include "core/property/KeyableProperty.hpp"
#include "core/property/PropertyManager.hpp"

namespace maudio{

class IAction{
public:
	virtual ~IAction(){};

	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept = 0;
	virtual IAudioInfo *getInfo() noexcept = 0;

	virtual void addSocket(ISocket *socket, int slot) = 0;
	virtual void removeSocket(int slot) = 0;

	virtual int NumInputs() const = 0;
	virtual int NumOutputs() const = 0;

	virtual int MaxInputs() const = 0;
	virtual bool HasOutputs() const = 0;

	virtual void readConfig(const KeyValueStore &conf) = 0;

	virtual PropertyManager *getProperties() = 0;

	virtual IKeyValueStore *serialize() const = 0;
	virtual void deserialize(const IKeyValueStore *data) = 0;
};

} // maudio

#endif // MAUDIO_HEADER




