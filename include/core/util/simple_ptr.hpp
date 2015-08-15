/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SIMPLEPTR
#define MAUDIO_SIMPLEPTR

#include <cstddef>

namespace maudio{

/**
Takes ownership over a pointer, acts like a pointer,
but deletes it when it goes out of scope.
Similar to stl smart pointers but has less overhead.
Best way to handle returned raw pointers.
Warning: its not thread save!
*/
template<typename T>
class simple_ptr{
public:
	simple_ptr(T *data = NULL);
	simple_ptr(simple_ptr<T> &data);
	~simple_ptr();

	void reset(T *data = NULL);
	void reset(simple_ptr<T> &data);
	T *release();

	T *get() const;
	T *operator->() const;
	T &operator*() const;

	void operator=(T &data);
	void operator=(simple_ptr<T> &data);
	bool operator==(simple_ptr<T> &data) const;
	operator bool() const;
	bool operator!() const;

private:
	T *mData = NULL;
};


template<typename T>
simple_ptr<T>::simple_ptr(T *data){
	reset(data);
	return;
}

template<typename T>
simple_ptr<T>::simple_ptr(simple_ptr<T> &data){
	reset(data);
	return;
}

template<typename T>
simple_ptr<T>::~simple_ptr(){
	reset();
	return;
}

template<typename T>
void simple_ptr<T>::reset(T *data){
	if(mData != NULL){
		delete mData;
	}
	mData = data;
	return;
}

template<typename T>
void simple_ptr<T>::reset(simple_ptr<T> &data){
	if(mData != NULL){
		delete mData;
	}
	mData = data.release();
	return;
}

template<typename T>
T *simple_ptr<T>::release(){
	T *ret = mData;
	mData = NULL;
	return ret;
}

template<typename T>
T *simple_ptr<T>::get() const{
	return mData;
}

template<typename T>
T *simple_ptr<T>::operator->() const{
	return mData;
}

template<typename T>
T &simple_ptr<T>::operator*() const{
	return *mData;
}

template<typename T>
void simple_ptr<T>::operator=(T &data){
	return reset(data);
}

template<typename T>
void simple_ptr<T>::operator=(simple_ptr<T> &data){
	return reset(data);
}

template<typename T>
bool simple_ptr<T>::operator==(simple_ptr<T> &data) const{
	if(mData == data.mData) return true;
	return false;
}

template<typename T>
simple_ptr<T>::operator bool() const{
	if(mData) return true;
	return false;
}

template<typename T>
bool simple_ptr<T>::operator!() const{
	if(mData) return false;
	return true;
}

} // maudio

#endif // MAUDIO_SIMPLEPTR




