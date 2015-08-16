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
	virtual ~BaseObservable();

	virtual void addObserver(IObserver *observer);
	virtual void removeObserver(IObserver *observer);
	virtual void notifyObservers(NoticeType type, const char *message = NULL);

private:
	std::vector<IObserver *> mObservers;
	std::mutex mMutex;
};

} // maudio

#endif // MAUDIO_BASEOBSERVABLE




