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
	std::lock_guard<std::mutex> lock(mMutex);
	if(!origin) return;
	mObserving.push_back(origin);
	return;
}

void BaseObserver::onRemove(IObservable *origin){
	std::lock_guard<std::mutex> lock(mMutex);
	if(!origin) return;
	for(unsigned int i = 0; i < mObserving.size(); i++){
		if(mObserving[i] == origin){
			mObserving.erase(mObserving.begin() + i);
			i--;
		}
	}
	return;
}

} // maudio



