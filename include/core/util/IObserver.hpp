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

	virtual void notify(const IObservable *origin, NoticeType type, const char *message) = 0;

protected:
	virtual void onAdd(IObservable *origin) = 0;
	virtual void onRemove(IObservable *origin) = 0;

	friend class IObservable;
	friend class BaseObservable;
};

} // maudio

#endif // MAUDIO_IOBSERVER




