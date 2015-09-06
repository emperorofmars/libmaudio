/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_BASEACTION
#define MAUDIO_BASEACTION

#include "maudio/action/IAction.hpp"
#include "maudio/property/PropertyManager.hpp"
#include "maudio/audiodata/AudioBuffer.hpp"
#include "maudio/audiodata/AudioInfo.hpp"
#include "maudio/util/sptr.hpp"
#include <vector>
#include <string>
#include <mutex>

namespace maudio{

class BaseAction : public IAction{
public:
	virtual ~BaseAction();

	virtual void setName(const char *name);
	virtual const char *getName() const;

	virtual void deleteData(IAudioBuffer *data) noexcept final;
	virtual void deleteData(IAudioInfo *data) noexcept final;
	virtual void deleteData(ISample *data) noexcept final;

	virtual bool addInput(IAction *input, int slot) final;
	virtual void removeInput(IAction *input) final;
	virtual void removeInput(int slot) final;
	virtual IAction *getInput(int slot) final;

	virtual unsigned int NumInputs() const final;

	virtual IPropertyManager *getProperties() final;

	virtual IControl *getControl();

	virtual bool checkCompatible(IAudioInfo *info);

	virtual void notify(const IObservable *origin, NoticeType type, const char *message) final;

protected:
	virtual bool checkCycles(IAction *node) const final;

	virtual bool InputOk(unsigned int slot) final;
	virtual sptr<IAudioBuffer> getFromSlot(unsigned int slot, unsigned long pos, unsigned int length) final;
	virtual sptr<IAudioInfo> getInfoFromSlot(unsigned int slot) final;
	virtual sptr<ISample> getSampleFromBuffer(unsigned int numSample, sptr<IAudioBuffer> buffer) final;
	
	virtual void onNotifyChange(const IObservable *origin, const char *message);
	virtual void onAdd(unsigned int slot);
	virtual void onRemove(unsigned int slot);
	
	PropertyManager mProperties;
	
	mutable std::recursive_mutex mMutex;
	
private:
	std::string mName;
	std::vector<IAction *> mInputs;
};

} // maudio

#endif // MAUDIO_BASEACTION




