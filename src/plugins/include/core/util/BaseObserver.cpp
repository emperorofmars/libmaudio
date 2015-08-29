/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/BaseObserver.hpp"

namespace maudio{

BaseObserver::~BaseObserver(){
	for(unsigned int i = 0; i < mObserving.size(); i++){
		mObserving[i]->removeObserver(this);
	}
	return;
}

void BaseObserver::onAdd(IObservable *origin){
	if(!origin) return;
	mMutex.lock();
	mObserving.push_back(origin);
	mMutex.unlock();
	return;
}

void BaseObserver::onRemove(IObservable *origin){
	if(!origin) return;
	mMutex.lock();
	for(unsigned int i = 0; i < mObserving.size(); i++){
		if(mObserving[i] == origin){
			mObserving.erase(mObserving.begin() + i);
			i--;
		}
	}
	mMutex.unlock();
	return;
}

} // maudio



