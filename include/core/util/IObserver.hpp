/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IOBSERVER
#define MAUDIO_IOBSERVER

namespace maudio{

enum NoticeType{
	ON_CHANGE,
	ON_DELETE
};

class IObservable;

class IObserver{
public:
	virtual ~IObserver(){};

	virtual void notify(const IObservable *Origin, NoticeType type, const char *message) = 0;
};

} // maudio

#endif // MAUDIO_IOBSERVER




