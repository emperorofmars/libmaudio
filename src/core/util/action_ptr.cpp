/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/action_ptr.hpp"

namespace maudio{

template<>
void action_ptr<IAudioBuffer>::reset(IAudioBuffer *data, IAction *deleter){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				if(mDeleter != NULL){
					mDeleter->deleteData(mData);
				}
				else{
					delete mData;
				}
			}
			if(mRefCount->mRefs == 0){
				delete mRefCount;
			}
			mRefCount = NULL;
		}
		else{
			if(mDeleter != NULL){
				mDeleter->deleteData(mData);
			}
			else{
				delete mData;
			}
		}
	}
	mData = data;
	mDeleter = deleter;

	mRefCount = new RefCount();
	mRefCount->mRefs = 1;
	return;
}

template<>
void action_ptr<IAudioInfo>::reset(IAudioInfo *data, IAction *deleter){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				if(mDeleter != NULL){
					mDeleter->deleteData(mData);
				}
				else{
					delete mData;
				}
			}
			if(mRefCount->mRefs == 0){
				delete mRefCount;
			}
			mRefCount = NULL;
		}
		else{
			if(mDeleter != NULL){
				mDeleter->deleteData(mData);
			}
			else{
				delete mData;
			}
		}
	}
	mData = data;
	mDeleter = deleter;

	mRefCount = new RefCount();
	mRefCount->mRefs = 1;
	return;
}

template<>
void action_ptr<ISample>::reset(ISample *data, IAction *deleter){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				if(mDeleter != NULL){
					mDeleter->deleteData(mData);
				}
				else{
					delete mData;
				}
			}
			if(mRefCount->mRefs == 0){
				delete mRefCount;
			}
			mRefCount = NULL;
		}
		else{
			if(mDeleter != NULL){
				mDeleter->deleteData(mData);
			}
			else{
				delete mData;
			}
		}
	}
	mData = data;
	mDeleter = deleter;

	mRefCount = new RefCount();
	mRefCount->mRefs = 1;
	return;
}

template<>
void action_ptr<IAudioBuffer>::reset(const action_ptr<IAudioBuffer> &data){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				if(mDeleter != NULL){
					mDeleter->deleteData(mData);
				}
				else{
					delete mData;
				}
			}
			if(mRefCount->mRefs == 0){
				delete mRefCount;
			}
			mRefCount = NULL;
		}
		else{
			if(mDeleter != NULL){
				mDeleter->deleteData(mData);
			}
			else{
				delete mData;
			}
		}
	}
	mData = data.get();
	mRefCount = data.mRefCount;
	mRefCount->mRefs++;
	return;
}

template<>
void action_ptr<IAudioInfo>::reset(const action_ptr<IAudioInfo> &data){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				if(mDeleter != NULL){
					mDeleter->deleteData(mData);
				}
				else{
					delete mData;
				}
			}
			if(mRefCount->mRefs == 0){
				delete mRefCount;
			}
			mRefCount = NULL;
		}
		else{
			if(mDeleter != NULL){
				mDeleter->deleteData(mData);
			}
			else{
				delete mData;
			}
		}
	}
	mData = data.get();
	mRefCount = data.mRefCount;
	mRefCount->mRefs++;
	return;
}

template<>
void action_ptr<ISample>::reset(const action_ptr<ISample> &data){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				if(mDeleter != NULL){
					mDeleter->deleteData(mData);
				}
				else{
					delete mData;
				}
			}
			if(mRefCount->mRefs == 0){
				delete mRefCount;
			}
			mRefCount = NULL;
		}
		else{
			if(mDeleter != NULL){
				mDeleter->deleteData(mData);
			}
			else{
				delete mData;
			}
		}
	}
	mData = data.get();
	mRefCount = data.mRefCount;
	mRefCount->mRefs++;
	return;
}

} // maudio



