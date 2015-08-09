/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_BASEACTION
#define MAUDIO_BASEACTION

#include "core/node/IAction.hpp"
#include "core/property/PropertyManager.hpp"
#include "core/audiodata/AudioBuffer.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <vector>

namespace maudio{

class BaseAction : public IAction{
public:
	virtual ~BaseAction();

	virtual void addSocket(ISocket *socket, int slot) final;
	virtual void removeSocket(int slot) final;

	virtual int NumInputs() const final;

	virtual IPropertyManager *getProperties() final;

	virtual IControl *getControl();

protected:
	PropertyManager mProperties;
	std::vector<ISocket *> mInputs;
};

} // maudio

#endif // MAUDIO_BASEACTION




