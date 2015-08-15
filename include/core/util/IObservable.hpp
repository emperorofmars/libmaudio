/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IOBSERVABLE
#define MAUDIO_IOBSERVABLE

#include "core/util/IObserver.hpp"

namespace maudio{

class IObservable{
public:
	virtual ~IObservable(){onChange(ON_DELETE);};

	virtual addObserver(IObserver *mObserver) = 0;
	virtual removeObserver(IObserver *mObserver) = 0;
	virtual notifyObservers(NoticeType type, const char *message = NULL) = 0;
};

} // maudio

#endif // MAUDIO_IOBSERVABLE




