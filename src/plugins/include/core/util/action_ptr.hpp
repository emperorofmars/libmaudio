/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ACTIONPTR
#define MAUDIO_ACTIONPTR

#include <cstddef>
#include "core/node/IAudioGetter.hpp"

namespace maudio{

/**
Takes ownership over a pointer, acts like a pointer,
but deletes it when it goes out of scope.
Similar to stl smart pointers but has less overhead.
Best way to handle returned raw pointers.
Warning: its not thread save!
*/
template<typename T>
class action_ptr{
public:
	action_ptr(T *data = NULL, IAudioGetter *deleter = NULL);
	action_ptr(const action_ptr<T> &data);
	~action_ptr();

	void reset(T *data = NULL, IAudioGetter *deleter = NULL);
	void reset(const action_ptr<T> &data);
	T *release();

	T *get() const;
	T *operator->() const;
	T &operator*() const;

	void operator=(T &data);
	void operator=(const action_ptr<T> &data);
	bool operator==(const action_ptr<T> &data) const;
	operator bool() const;
	bool operator!() const;

private:
	struct RefCount{
		int mRefs = 0;
	};

	T *mData = NULL;
	IAudioGetter *mDeleter = NULL;
	RefCount *mRefCount = NULL;
};


template<typename T>
action_ptr<T>::action_ptr(T *data, IAudioGetter *deleter){
	reset(data);
	return;
}

template<typename T>
action_ptr<T>::action_ptr(const action_ptr<T> &data){
	reset(data);
	return;
}

template<typename T>
action_ptr<T>::~action_ptr(){
	reset();
	return;
}

template<typename T>
void action_ptr<T>::reset(T *data, IAudioGetter *deleter){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				delete mData;
			}
			if(mRefCount->mRefs == 0){
				delete mRefCount;
			}
			mRefCount = NULL;
		}
		else{
			delete mData;
		}
	}
	mData = data;
	mDeleter = deleter;

	mRefCount = new RefCount();
	mRefCount->mRefs = 1;
	return;
}

template<typename T>
void action_ptr<T>::reset(const action_ptr<T> &data){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				delete mData;
			}
			if(mRefCount->mRefs == 0){
				delete mRefCount;
			}
			mRefCount = NULL;
		}
		else{
			delete mData;
		}
	}
	mData = data.get();
	mRefCount = data.mRefCount;
	mRefCount->mRefs++;
	return;
}

template<typename T>
T *action_ptr<T>::release(){
	T *ret = mData;
	mData = NULL;
	return ret;
}

template<typename T>
T *action_ptr<T>::get() const{
	return mData;
}

template<typename T>
T *action_ptr<T>::operator->() const{
	return mData;
}

template<typename T>
T &action_ptr<T>::operator*() const{
	return *mData;
}

template<typename T>
void action_ptr<T>::operator=(T &data){
	return reset(data);
}

template<typename T>
void action_ptr<T>::operator=(const action_ptr<T> &data){
	return reset(data);
}

template<typename T>
bool action_ptr<T>::operator==(const action_ptr<T> &data) const{
	if(mData == data.mData) return true;
	return false;
}

template<typename T>
action_ptr<T>::operator bool() const{
	if(mData) return true;
	return false;
}

template<typename T>
bool action_ptr<T>::operator!() const{
	if(mData) return false;
	return true;
}

} // maudio

#endif // MAUDIO_ACTIONPTR




