/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_BASEOBSERVABLE
#define MAUDIO_BASEOBSERVABLE

#include "core/util/IObservable.hpp"
#include <vector>
#include <mutex>

namespace maudio{

class BaseObservable{
public:
	BaseObservable();
	virtual ~BaseObservable();

	virtual void addObserver(IObserver *observer) final;
	virtual void removeObserver(IObserver *observer) final;
	virtual void notifyObservers(NoticeType type, const char *message = NULL) final;

	virtual unsigned long getObservableID() const final;

private:
	std::vector<IObserver *> mObservers;
	std::mutex mMutex;

	unsigned long mObservableID;
	static unsigned long mGlobalObservableID;
};

} // maudio

#endif // MAUDIO_BASEOBSERVABLE




