/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "maudio/util/sptr.hpp"
#include <typeinfo>

namespace maudio{

template<>
void sptr<IAction>::clear(){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(mData != NULL){
		mRefCount->mRefs--;
		if(mRefCount->mRefs == 0){
			if(mDefaultDeleter){
				mDefaultDeleter->deleteData(mData);
				if(mDeleterOwned) delete mDefaultDeleter;
			}
			else if(mPluginDeleter){
				mPluginDeleter->deleteInstance(mData);
			}
			else delete mData;
			delete mRefCount;
		}
	}
	mData = NULL;
	mDefaultDeleter = NULL;
	mActionDeleter = NULL;
	mPluginDeleter = NULL;
	mRefCount = NULL;
	return;
}

template<>
void sptr<IAudioBuffer>::clear(){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(mData != NULL){
		mRefCount->mRefs--;
		if(mRefCount->mRefs == 0){
			if(mDefaultDeleter){
				mDefaultDeleter->deleteData(mData);
				if(mDeleterOwned) delete mDefaultDeleter;
			}
			else if(mActionDeleter){
				mActionDeleter->deleteData(mData);
			}
			else delete mData;
			delete mRefCount;
		}
	}
	mData = NULL;
	mDefaultDeleter = NULL;
	mActionDeleter = NULL;
	mPluginDeleter = NULL;
	mRefCount = NULL;
	return;
}

template<>
void sptr<IAudioInfo>::clear(){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(mData != NULL){
		mRefCount->mRefs--;
		if(mRefCount->mRefs == 0){
			if(mDefaultDeleter){
				mDefaultDeleter->deleteData(mData);
				if(mDeleterOwned) delete mDefaultDeleter;
			}
			else if(mActionDeleter){
				mActionDeleter->deleteData(mData);
			}
			else delete mData;
			delete mRefCount;
		}
	}
	mData = NULL;
	mDefaultDeleter = NULL;
	mActionDeleter = NULL;
	mPluginDeleter = NULL;
	mRefCount = NULL;
	return;
}

template<>
void sptr<ISample>::clear(){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(mData != NULL){
		mRefCount->mRefs--;
		if(mRefCount->mRefs == 0){
			if(mDefaultDeleter){
				mDefaultDeleter->deleteData(mData);
				if(mDeleterOwned) delete mDefaultDeleter;
			}
			else if(mActionDeleter){
				mActionDeleter->deleteData(mData);
			}
			else delete mData;
			delete mRefCount;
		}
	}
	mData = NULL;
	mDefaultDeleter = NULL;
	mActionDeleter = NULL;
	mPluginDeleter = NULL;
	mRefCount = NULL;
	return;
}

} // maudio










