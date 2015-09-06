/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IACTION
#define MAUDIO_IACTION

#include "maudio/util/UniqueID.hpp"
#include "maudio/action/IControl.hpp"
#include "maudio/util/BaseObserver.hpp"
#include "maudio/util/BaseObservable.hpp"
#include "maudio/audiodata/IAudioBuffer.hpp"
#include "maudio/audiodata/IAudioInfo.hpp"
#include "maudio/property/IProperty.hpp"
#include "maudio/property/IKeyableProperty.hpp"
#include "maudio/property/IPropertyManager.hpp"
#include "maudio/store/IKeyValueStore.hpp"
#include "maudio/store/IMultiLevelStore.hpp"
#include "maudio/serializer/ISerializable.hpp"

namespace maudio{

class IAction : public UniqueID, public ISerializable, public BaseObserver, public BaseObservable{
public:
	virtual ~IAction(){};

	virtual void setName(const char *name) = 0;
	virtual const char *getName() const = 0;

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

	virtual void readConfig(const IKeyValueStore *conf) = 0;

	virtual IPropertyManager *getProperties() = 0;

	virtual IControl *getControl() = 0;

	virtual bool checkCompatible(IAudioInfo *info) = 0;

protected:
	virtual bool checkCycles(IAction *node) const = 0;
};

} // maudio

#endif // MAUDIO_HEADER




