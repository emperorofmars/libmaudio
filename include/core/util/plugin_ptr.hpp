/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PLUGINPTR
#define MAUDIO_PLUGINPTR

#include "core/pluginmanager/PluginLoader.hpp"
#include <cstddef>

#include <iostream>

namespace maudio{

/**
Takes ownership over a pointer to a plugin instance,
acts like a pointer, but deletes it when it goes out of scope,
unless there are other plugin_ptr instances assigned from it.
Similar to stl smart pointers but has less overhead.
Best way to handle returned raw pointers.
Warning: its not thread save!
*/
template<typename T>
class plugin_ptr{
public:
	plugin_ptr(T *data = NULL, PluginLoader<T> *deleter = NULL);
	plugin_ptr(const plugin_ptr<T> &data);
	~plugin_ptr();

	void reset(T *data = NULL, PluginLoader<T> *deleter = NULL);
	void reset(const plugin_ptr<T> &data);
	T *release();

	T *get() const;
	T *operator->() const;
	T &operator*() const;

	void operator=(T &data);
	void operator=(const plugin_ptr<T> &data);
	bool operator==(const plugin_ptr<T> &data) const;
	operator bool() const;
	bool operator!() const;

private:
	struct RefCount{
		int mRefs = 0;
	};

	T *mData = NULL;
	PluginLoader<T> *mDeleter = NULL;
	RefCount *mRefCount = NULL;
};


template<typename T>
plugin_ptr<T>::plugin_ptr(T *data, PluginLoader<T> *deleter){
	reset(data, deleter);
	return;
}

template<typename T>
plugin_ptr<T>::plugin_ptr(const plugin_ptr<T> &data){
	reset(data);
	return;
}

template<typename T>
plugin_ptr<T>::~plugin_ptr(){
	reset();
	return;
}

template<typename T>
void plugin_ptr<T>::reset(T *data, PluginLoader<T> *deleter){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				if(mDeleter != NULL){
					mDeleter->deleteInstance(mData);
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
				mDeleter->deleteInstance(mData);
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

template<typename T>
void plugin_ptr<T>::reset(const plugin_ptr<T> &data){
	if(mData != NULL){
		if(mRefCount){
			mRefCount->mRefs--;
			if(mRefCount->mRefs == 0){
				if(mDeleter != NULL){
					mDeleter->deleteInstance(mData);
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
				mDeleter->deleteInstance(mData);
			}
			else{
				delete mData;
			}
		}
	}
	mData = data.get();
	mDeleter = data.mDeleter;
	mRefCount = data.mRefCount;
	mRefCount->mRefs++;
	return;
}

template<typename T>
T *plugin_ptr<T>::release(){
	T *ret = mData;
	mData = NULL;
	return ret;
}

template<typename T>
T *plugin_ptr<T>::get() const{
	return mData;
}

template<typename T>
T *plugin_ptr<T>::operator->() const{
	return mData;
}

template<typename T>
T &plugin_ptr<T>::operator*() const{
	return *mData;
}

template<typename T>
void plugin_ptr<T>::operator=(T &data){
	return reset(data);
}

template<typename T>
void plugin_ptr<T>::operator=(const plugin_ptr<T> &data){
	return reset(data);
}

template<typename T>
bool plugin_ptr<T>::operator==(const plugin_ptr<T> &data) const{
	if(mData == data.mData) return true;
	return false;
}

template<typename T>
plugin_ptr<T>::operator bool() const{
	if(mData) return true;
	return false;
}

template<typename T>
bool plugin_ptr<T>::operator!() const{
	if(mData) return false;
	return true;
}

} // maudio

#endif // MAUDIO_PLUGINPTR




