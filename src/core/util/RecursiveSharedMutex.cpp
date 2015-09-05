/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/RecursiveSharedMutex.hpp"

#include <iostream>

namespace maudio{

recursive_shared_mutex::recursive_shared_mutex(){
	return;
}

recursive_shared_mutex::~recursive_shared_mutex(){
	return;
}

void recursive_shared_mutex::lock(){
	mMutex.lock();
	mSharedMutex.lock();
	return;
}

bool recursive_shared_mutex::try_lock(){
	if(!mMutex.try_lock()) return false;
	if(!mSharedMutex.try_lock()){
		mMutex.unlock();
		return false;
	}
	return true;
}

void recursive_shared_mutex::unlock(){
	mSharedMutex.unlock();
	mMutex.unlock();
	return;
}

void recursive_shared_mutex::lock_shared(){
	mMutex.lock();
	mSharedMutex.try_lock();
	mLockLevel++;
	mMutex.unlock();
	return;
}

bool recursive_shared_mutex::try_lock_shared(){
	if(!mMutex.try_lock()) return false;
	if(!mSharedMutex.try_lock()){
		mMutex.unlock();
		return false;
	}
	mLockLevel++;
	mMutex.unlock();
	return true;
}

void recursive_shared_mutex::unlock_shared(){
	mLockLevel--;
	if(mLockLevel == 0){
		mSharedMutex.unlock();
	}
	return;
}

} // maudio



