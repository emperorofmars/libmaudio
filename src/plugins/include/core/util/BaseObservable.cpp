/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/BaseObservable.hpp"

namespace maudio{

BaseObservable::~BaseObservable(){
	notifyObservers(ON_DELETE);
}

void BaseObservable::addObserver(IObserver *observer){
	if(!observer) return;
	mMutex.lock();
	for(unsigned int i = 0; i < mObservers.size(); i++){
		if(mObservers[i] == observer){
			mMutex.unlock();
			return; //if it has been already added
		}
	}
	mObservers.push_back(observer);
	observer->onAdd((IObservable *)this);
	mMutex.unlock();
	return;
}

void BaseObservable::removeObserver(IObserver *observer){
	if(!observer) return;
	mMutex.lock();
	for(unsigned int i = 0; i < mObservers.size(); i++){
		if(mObservers[i] == observer){
			mObservers.erase(mObservers.begin() + i);
			i--;
		}
	}
	mMutex.unlock();
	return;
}

void BaseObservable::notifyObservers(NoticeType type, const char *message){
	mMutex.lock();
	for(unsigned int i = 0; i < mObservers.size(); i++){
		mObservers[i]->notify((const IObservable *)this, type, message);
	}
	if(type == ON_DELETE){
		for(unsigned int i = 0; i < mObservers.size(); i++){
			mObservers[i]->onRemove((IObservable *)this);
		}
	}
	mMutex.unlock();
	return;
}

} // maudio






