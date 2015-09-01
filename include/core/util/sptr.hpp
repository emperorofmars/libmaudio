/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SPTR
#define MAUDIO_SPTR

#include "core/action/IAction.hpp"
#include "core/pluginmanager/PluginLoader.hpp"
#include <cstddef>

namespace maudio{

/**
Similar to stl smart pointers but has less overhead.
Can use special maudio deleters.
Best way to handle returned raw pointers.
Warning: its not thread save!
*/

template<typename T>
struct DefaultDeleter{
	void deleteData(T *data){
		delete data;
	};
};

template<typename T>
class sptr{
public:
	sptr(T *data = NULL, DefaultDeleter<T> *deleter = NULL);
	sptr(T *data, IAction *deleter);
	sptr(T *data, PluginLoader<T> *deleter);
	sptr(const sptr<T> &data);
	~sptr();

	void reset(T *data = NULL, DefaultDeleter<T> *deleter = NULL);
	void reset(T *data, IAction *deleter);
	void reset(T *data, PluginLoader<T> *deleter);
	void reset(const sptr<T> &data);
	T *release();

	T *get() const;
	T *operator->() const;
	T &operator*() const;

	void operator=(T &data);
	void operator=(const sptr<T> &data);
	bool operator==(const sptr<T> &data) const;
	operator bool() const;
	bool operator!() const;

	DefaultDeleter<T> *getDefaultDeleter() const;
	IAction *getActionDeleter() const;
	PluginLoader<T> *getPluginDeleter() const;

private:
	void clear();

	struct RefCount{
		int mRefs = 0;
	};

	T *mData = NULL;
	DefaultDeleter<T> *mDefaultDeleter = NULL;
	IAction *mActionDeleter = NULL;
	PluginLoader<T> *mPluginDeleter = NULL;
	bool mDeleterOwned = false;
	RefCount *mRefCount = new RefCount();
};


template<typename T>
sptr<T>::sptr(T *data, DefaultDeleter<T> *deleter){
	reset(data, deleter);
	return;
}

template<typename T>
sptr<T>::sptr(T *data, IAction *deleter){
	reset(data, deleter);
	return;
}

template<typename T>
sptr<T>::sptr(T *data, PluginLoader<T> *deleter){
	reset(data, deleter);
	return;
}

template<typename T>
sptr<T>::sptr(const sptr<T> &data){
	reset(data);
	return;
}

template<typename T>
sptr<T>::~sptr(){
	reset();
	return;
}

template<typename T>
void sptr<T>::reset(T *data, DefaultDeleter<T> *deleter){
	clear();

	mData = data;
	mDefaultDeleter = deleter;

	if(mData != NULL && mDefaultDeleter == NULL){
		mDefaultDeleter = new DefaultDeleter<T>();
		mDeleterOwned = true;
	}
	else{
		mDeleterOwned = false;
	}

	mRefCount = new RefCount();
	mRefCount->mRefs = 1;
	return;
}

template<typename T>
void sptr<T>::reset(T *data, IAction *deleter){
	clear();

	mData = data;
	mActionDeleter = deleter;

	if(mData != NULL && mActionDeleter == NULL){
		mDefaultDeleter = new DefaultDeleter<T>();
		mDeleterOwned = true;
	}
	else{
		mDeleterOwned = false;
	}

	mRefCount = new RefCount();
	mRefCount->mRefs = 1;
	return;
}

template<typename T>
void sptr<T>::reset(T *data, PluginLoader<T> *deleter){
	clear();

	mData = data;
	mPluginDeleter = deleter;

	if(mData != NULL && mPluginDeleter == NULL){
		mDefaultDeleter = new DefaultDeleter<T>();
		mDeleterOwned = true;
	}
	else{
		mDeleterOwned = false;
	}

	mRefCount = new RefCount();
	mRefCount->mRefs = 1;
	return;
}

template<typename T>
void sptr<T>::reset(const sptr<T> &data){
	clear();

	mData = data.get();
	mDefaultDeleter = data.mDefaultDeleter;
	mActionDeleter = data.mActionDeleter;
	mPluginDeleter = data.mPluginDeleter;

	if(!mDefaultDeleter && !mActionDeleter && !mPluginDeleter){
		mDefaultDeleter = new DefaultDeleter<T>();
		mDeleterOwned = true;
	}
	else{
		mDeleterOwned = false;
	}

	mRefCount = data.mRefCount;
	mRefCount->mRefs++;
	return;
}

template<typename T>
T *sptr<T>::release(){
	T *ret = mData;
	if(mData != NULL){
		mRefCount->mRefs--;
		if(mRefCount->mRefs == 0){
			if(mDeleterOwned) delete mDefaultDeleter;
			delete mRefCount;
		}
	}
	mData = NULL;
	mDefaultDeleter = NULL;
	mActionDeleter = NULL;
	mPluginDeleter = NULL;
	mRefCount = NULL;
	return ret;
}

template<typename T>
T *sptr<T>::get() const{
	return mData;
}

template<typename T>
T *sptr<T>::operator->() const{
	return mData;
}

template<typename T>
T &sptr<T>::operator*() const{
	return *mData;
}

template<typename T>
void sptr<T>::operator=(T &data){
	return reset(data);
}

template<typename T>
void sptr<T>::operator=(const sptr<T> &data){
	return reset(data);
}

template<typename T>
bool sptr<T>::operator==(const sptr<T> &data) const{
	if(mData == data.mData) return true;
	return false;
}

template<typename T>
sptr<T>::operator bool() const{
	if(mData) return true;
	return false;
}

template<typename T>
bool sptr<T>::operator!() const{
	if(mData) return false;
	return true;
}

template<typename T>
DefaultDeleter<T> *sptr<T>::getDefaultDeleter() const{
	return mDefaultDeleter;
}

template<typename T>
IAction *sptr<T>::getActionDeleter() const{
	return mActionDeleter;
}

template<typename T>
PluginLoader<T> *sptr<T>::getPluginDeleter() const{
	return mPluginDeleter;
}

template<typename T>
void sptr<T>::clear(){
	if(mData != NULL){
		mRefCount->mRefs--;
		if(mRefCount->mRefs == 0){
			if(mDefaultDeleter){
				mDefaultDeleter->deleteData(mData);
				if(mDeleterOwned) delete mDefaultDeleter;
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

#endif // MAUDIO_SPTR




