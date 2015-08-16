/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_BASEOBSERVER
#define MAUDIO_BASEOBSERVER

#include "core/util/IObserver.hpp"
#include "core/util/IObservable.hpp"
#include <vector>
#include <mutex>

namespace maudio{

class BaseObserver : public IObserver{
public:
	virtual ~BaseObserver();

private:
	virtual void onAdd(IObservable *origin) final;
	virtual void onRemove(IObservable *origin) final;

	std::vector<IObservable *> mObserving;
	std::mutex mMutex;
};

} // maudio

#endif // MAUDIO_BASEOBSERVER




