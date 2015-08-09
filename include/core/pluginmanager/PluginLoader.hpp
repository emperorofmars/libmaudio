/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PLUGINLOADER
#define MAUDIO_PLUGINLOADER

#include "core/util/AudioException.hpp"
#include <dlfcn.h>

namespace maudio{

typedef void *create_t();
typedef void destroy_t(void *data);

template<typename T>
class PluginLoader{
public:
	PluginLoader(const char *path = NULL);
	~PluginLoader();

	void loadPlugin(const char *path);
	void unloadPlugin();

	bool loaded();

	T *createInstance();
	void deleteInstance(T *data);

private:
    void *mHandle = NULL;
    create_t *mCreateFunc = NULL;
    destroy_t *mDestroyFunc = NULL;
};


template<typename T>
PluginLoader<T>::PluginLoader(const char *path){
	if(path) loadPlugin(path);
	return;
}

template<typename T>
PluginLoader<T>::~PluginLoader(){
	if(loaded()){
		unloadPlugin();
	}
	return;
}

template<typename T>
void PluginLoader<T>::loadPlugin(const char *path){
	mHandle = dlopen(path, RTLD_LAZY);
	if(!mHandle){
		throw MaudioException("cannot open plugin");
	}
	dlerror();

	mCreateFunc = (create_t *)dlsym(mHandle, "create");
	const char* dlsym_error = dlerror();
	if(dlsym_error){
		throw MaudioException("cannot load create function");
	}

	mDestroyFunc = (destroy_t *)dlsym(mHandle, "destroy");
	dlsym_error = dlerror();
	if(dlsym_error){
		throw MaudioException("cannot load create function");
	}
	return;
}

template<typename T>
void PluginLoader<T>::unloadPlugin(){
	if(loaded()){
		dlclose(mHandle);
		mHandle = NULL;
		mCreateFunc = NULL;
		mDestroyFunc = NULL;
	}
	return;
}

template<typename T>
bool PluginLoader<T>::loaded(){
	if(mHandle) return true;
	return false;
}

template<typename T>
T *PluginLoader<T>::createInstance(){
	return (T *)mCreateFunc();
}

template<typename T>
void PluginLoader<T>::deleteInstance(T *data){
	mDestroyFunc(data);
	return;
}

} // maudio

#endif // MAUDIO_PLUGINLOADER




