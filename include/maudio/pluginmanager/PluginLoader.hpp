/*
* Project Maudio
* Copyright (C) 2015 Martin Schwarz
* See LICENSE.txt for the full license
*/

#ifndef MAUDIO_PLUGINLOADER
#define MAUDIO_PLUGINLOADER

#include "maudio/util/String.hpp"
#include "maudio/util/BaseObservable.hpp"
#include "maudio/util/AudioException.hpp"
#include <dlfcn.h>
#include <string>

namespace maudio{

typedef void *create_t();
typedef void destroy_t(void *data);
typedef const char *getName_t();

template<typename T>
class PluginLoader : public BaseObservable{
public:
	PluginLoader(const char *path = NULL);
	~PluginLoader();

	void loadPlugin(const char *path);
	void unloadPlugin();

	bool loaded();

	std::string getName();
	std::string getPath();

	T *createInstance();
	void deleteInstance(T *data);

private:
	std::string mName;
	std::string mPath;
	
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
	dlerror();
	mHandle = dlopen(path, RTLD_LAZY);
	if(!mHandle){
		throw MaudioException(std::string("cannot open plugin: ").append(std::string(dlerror())));
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

	getName_t *nameFunc = (getName_t *)dlsym(mHandle, "getName");
	dlsym_error = dlerror();
	if(dlsym_error){
		throw MaudioException("cannot load getName function");
	}

	mPath = path;
	mName = nameFunc();
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
std::string PluginLoader<T>::getName(){
	return mName;
}

template<typename T>
std::string PluginLoader<T>::getPath(){
	return mPath;
}

template<typename T>
T *PluginLoader<T>::createInstance(){
	if(loaded()){
		return (T *)mCreateFunc();
	}
	return NULL;
}

template<typename T>
void PluginLoader<T>::deleteInstance(T *data){
	if(loaded()){
		mDestroyFunc(data);
	}
	return;
}

} // maudio

#endif // MAUDIO_PLUGINLOADER




