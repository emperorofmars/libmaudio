/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/util/BaseObserver.hpp"

namespace maudio{

unsigned long BaseObserver::mGlobalObserverID = 0;

BaseObserver::BaseObserver(){
	mGlobalObserverID++;
	mObserverID = mGlobalObserverID;
	return;
}

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
		if(mObserving[i]->getObservableID() == origin->getObservableID()){
			mObserving.erase(mObserving.begin() + i);
			i--;
		}
	}
	return;
}

unsigned long BaseObserver::getObserverID() const{
	std::lock_guard<std::mutex> lock(mMutex);
	return mObserverID;
}

} // maudio



