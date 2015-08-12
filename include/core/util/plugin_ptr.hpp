/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ACTIONPTR
#define MAUDIO_ACTIONPTR

#include <cstddef>
#include "core/pluginmanager/PluginLoader.hpp"

namespace maudio{

/**
Takes ownership over a pointer, acts like a pointer,
but deletes it when it goes out of scope.
Similar to stl smart pointers but has less overhead.
Best way to handle returned raw pointers.
Warning: its not thread save!
*/
template<typename T>
class plugin_ptr{
public:
	plugin_ptr();
	plugin_ptr(T *data, PluginLoader<T> *deleter);
	plugin_ptr(plugin_ptr<T> &data);
	~plugin_ptr();

	void reset();
	void reset(T *data, PluginLoader<T> *deleter);
	void reset(plugin_ptr<T> &data);
	T *release();

	T *get();
	T *operator->();
	T &operator*();

	void operator=(T &data);
	void operator=(plugin_ptr<T> &data);
	bool operator==(plugin_ptr<T> &data);
	operator bool();

private:
	T *mData = NULL;
	PluginLoader<T> *mDeleter = NULL;
};


template<typename T>
plugin_ptr<T>::plugin_ptr(){
	return;
}

template<typename T>
plugin_ptr<T>::plugin_ptr(T *data, PluginLoader<T> *deleter){
	reset(data, deleter);
	return;
}

template<typename T>
plugin_ptr<T>::plugin_ptr(plugin_ptr<T> &data){
	reset(data);
	return;
}

template<typename T>
plugin_ptr<T>::~plugin_ptr(){
	reset();
	return;
}

template<typename T>
void plugin_ptr<T>::reset(){
	if(mData != NULL){
		if(mDeleter != NULL){
			mDeleter->deleteInstance(mData);
		}
		else{
			delete mData;
		}
	}
	mData = NULL;
	mDeleter = NULL;
	return;
}

template<typename T>
void plugin_ptr<T>::reset(T *data, PluginLoader<T> *deleter){
	if(mData != NULL){
		if(mDeleter != NULL){
			mDeleter->deleteInstance(mData);
		}
		else{
			delete mData;
		}
	}
	mData = data;
	mDeleter = deleter;
	return;
}

template<typename T>
void plugin_ptr<T>::reset(plugin_ptr<T> &data){
	if(mData != NULL){
		if(mDeleter != NULL){
			mDeleter->deleteInstance(mData);
		}
		else{
			delete mData;
		}
	}
	mData = data.release();
	return;
}

template<typename T>
T *plugin_ptr<T>::release(){
	T *ret = mData;
	mData = NULL;
	return ret;
}

template<typename T>
T *plugin_ptr<T>::get(){
	return mData;
}

template<typename T>
T *plugin_ptr<T>::operator->(){
	return mData;
}

template<typename T>
T &plugin_ptr<T>::operator*(){
	return *mData;
}

template<typename T>
void plugin_ptr<T>::operator=(T &data){
	return reset(data);
}

template<typename T>
void plugin_ptr<T>::operator=(plugin_ptr<T> &data){
	return reset(data);
}

template<typename T>
bool plugin_ptr<T>::operator==(plugin_ptr<T> &data){
	if(mData == data.mData) return true;
	return false;
}

template<typename T>
plugin_ptr<T>::operator bool(){
	if(mData) return true;
	return false;
}

} // maudio

#endif // MAUDIO_ACTIONPTR




