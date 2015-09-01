/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IACTION
#define MAUDIO_IACTION

#include "core/util/UniqueID.hpp"
#include "core/action/IControl.hpp"
#include "core/util/BaseObserver.hpp"
#include "core/util/BaseObservable.hpp"
#include "core/audiodata/IAudioBuffer.hpp"
#include "core/audiodata/IAudioInfo.hpp"
#include "core/property/IProperty.hpp"
#include "core/property/IKeyableProperty.hpp"
#include "core/property/IPropertyManager.hpp"
#include "core/store/IKeyValueStore.hpp"
#include "core/store/IMultiLevelStore.hpp"
#include "core/serializer/ISerializable.hpp"

namespace maudio{

class IAction : public UniqueID, public ISerializable, public BaseObserver, public BaseObservable{
public:
	virtual ~IAction(){};

	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept = 0;
	virtual IAudioInfo *getInfo() noexcept = 0;

	virtual void deleteData(IAudioBuffer *data) noexcept = 0;
	virtual void deleteData(IAudioInfo *data) noexcept = 0;
	virtual void deleteData(ISample *data) noexcept = 0;

	virtual bool addInput(IAction *input, int slot) = 0;
	virtual void removeInput(IAction *input) = 0;
	virtual void removeInput(int slot) = 0;
	virtual IAction *getInput(int slot) = 0;

	virtual unsigned int NumInputs() const = 0;
	virtual int MaxInputs() const = 0;
	virtual bool HasOutputs() const = 0;

	virtual void readConfig(const IKeyValueStore &conf) = 0;

	virtual IPropertyManager *getProperties() = 0;

	virtual IControl *getControl() = 0;

	virtual bool checkCompatible(IAudioInfo *info) = 0;

protected:
	virtual bool checkCycles(IAction *node) const = 0;
};

} // maudio

#endif // MAUDIO_HEADER




