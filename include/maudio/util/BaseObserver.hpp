/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_BASEOBSERVER
#define MAUDIO_BASEOBSERVER

#include "maudio/util/IObserver.hpp"
#include "maudio/util/IObservable.hpp"
#include <vector>
#include <mutex>

namespace maudio{

class BaseObserver : public IObserver{
public:
	BaseObserver();
	virtual ~BaseObserver();
	
	virtual unsigned long getObserverID() const final;
	
private:
	virtual void onAdd(IObservable *origin) final;
	virtual void onRemove(IObservable *origin) final;

	std::vector<IObservable *> mObserving;
	mutable std::mutex mMutex;

	unsigned long mObserverID;
	static unsigned long mGlobalObserverID;
};

} // maudio

#endif // MAUDIO_BASEOBSERVER




