/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IOBSERVABLE
#define MAUDIO_IOBSERVABLE

#include "core/util/IObserver.hpp"
#include <cstddef>

namespace maudio{

class IObservable{
public:
	virtual ~IObservable(){};

	virtual void addObserver(IObserver *observer) = 0;
	virtual void removeObserver(IObserver *observer) = 0;
	virtual void notifyObservers(NoticeType type, const char *message = NULL) = 0;
};

} // maudio

#endif // MAUDIO_IOBSERVABLE




