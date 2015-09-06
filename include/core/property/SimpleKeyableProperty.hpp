/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SIMPLEKEYABLEPROPERTY
#define MAUDIO_SIMPLEKEYABLEPROPERTY

#include "core/property/IKeyableProperty.hpp"
#include "core/util/Util.hpp"
#include "core/util/AudioException.hpp"
#include <vector>
#include <limits>
#include <map>
#include <cmath>
#include <string>
#include <mutex>

namespace maudio{

template<typename T>
class SimpleKeyableProperty : public IKeyableProperty{
public:
	SimpleKeyableProperty(const char *name, T initialValue);
	virtual ~SimpleKeyableProperty();

	virtual const char *getName() const;

	virtual const char *getString(long double pos) const;
	virtual T get(long double pos) const;
	virtual const char *getKeyString(unsigned int keynum) const;
	virtual long double getKeyPos(unsigned int keynum) const;
	virtual T getKey(unsigned int keynum) const;
	virtual unsigned int getNumKeys() const;
	virtual void addKey(const char *value, long double pos);
	virtual void addKey(T value, long double pos);
	virtual void addKey(const std::string &value, long double pos);
	virtual void setKey(const char *value, unsigned int keynum);
	virtual void setKey(T value, unsigned int keynum);
	virtual void setKey(const std::string &value, unsigned int keynum);
	virtual void removeKey(unsigned int keynum);

	virtual void setBounds(T bottom, T upper);
	virtual const char *getBottomBoundsString() const;
	virtual const char *getUpperBoundsString() const;
	virtual std::vector<std::string> getBoundsString() const;
	virtual std::vector<T> getBounds() const;

	virtual void serialize(IMultiLevelStore *data) const;
	virtual void deserialize(const IMultiLevelStore *data);

private:
	T getElement(unsigned int pos) const;
	T interpolate(long double pos) const;

	std::string mName;
	std::map<long double, T> mValues;
	T mBottomBound;
	T mUpperBound;
	mutable std::recursive_mutex mMutex;
};

typedef SimpleKeyableProperty<bool> KeyableBoolProperty;
typedef SimpleKeyableProperty<int> KeyableIntProperty;
typedef SimpleKeyableProperty<unsigned int> KeyableUIntProperty;
typedef SimpleKeyableProperty<long> KeyableLongProperty;
typedef SimpleKeyableProperty<unsigned long> KeyableULongProperty;
typedef SimpleKeyableProperty<float> KeyableFloatProperty;
typedef SimpleKeyableProperty<double> KeyableDoubleProperty;
typedef SimpleKeyableProperty<std::string> KeyableStringProperty;

template<typename T>
SimpleKeyableProperty<T>::SimpleKeyableProperty(const char *name, T value){
	mName = name;
	mBottomBound = std::numeric_limits<T>::min();
	mUpperBound = std::numeric_limits<T>::max();
	addKey(value, 0);
}

template<typename T>
SimpleKeyableProperty<T>::~SimpleKeyableProperty(){
}

template<typename T>
const char *SimpleKeyableProperty<T>::getName() const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return mName.c_str();
}

template<typename T>
const char *SimpleKeyableProperty<T>::getString(long double pos) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return to_chararray(interpolate(pos));
}

template<typename T>
T SimpleKeyableProperty<T>::get(long double pos) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return interpolate(pos);
}

template<typename T>
const char *SimpleKeyableProperty<T>::getKeyString(unsigned int keynum) const{
	return to_chararray(getKey(keynum));
}

template<typename T>
long double SimpleKeyableProperty<T>::getKeyPos(unsigned int keynum) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(keynum >= mValues.size()) throw MaudioException("keynum out of range");
	auto iter = mValues.begin();
	while(iter != mValues.end() && keynum > 0){
		iter++;
		keynum--;
	}
	return iter->first;
}

template<typename T>
T SimpleKeyableProperty<T>::getKey(unsigned int keynum) const{
	return getElement(keynum);
}

template<typename T>
unsigned int SimpleKeyableProperty<T>::getNumKeys() const{
	return mValues.size();
}

template<typename T>
void SimpleKeyableProperty<T>::addKey(const std::string &value, long double pos){
	try{
		addKey(string_to<T>(value), pos);
	}
	catch(std::exception &e){
		throw MaudioException("failed to add value");
	}
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::addKey(T value, long double pos){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(value <= mBottomBound) value = mBottomBound;
	else if(value >= mUpperBound) value = mUpperBound;
	mValues[pos] = value;
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::addKey(const char *value, long double pos){
	addKey(std::string(value), pos);
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::setKey(const std::string &value, unsigned int keynum){
	try{
		setKey(string_to<T>(value), keynum);
	}
	catch(std::exception &e){
		throw MaudioException("failed to set value");
	}
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::setKey(T value, unsigned int keynum){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(keynum >= mValues.size()) return;
	if(value < mBottomBound) value = mBottomBound;
	else if(value > mUpperBound) value = mUpperBound;

	auto iter = mValues.begin();
	while(iter != mValues.end() && keynum > 0){
		iter++;
		keynum--;
	}
	iter->second = value;
	notifyObservers(ON_CHANGE);
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::setKey(const char *value, unsigned int keynum){
	setKey(std::string(value), keynum);
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::removeKey(unsigned int keynum){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(mValues.size() <= 1) return;
	if(keynum >= mValues.size()) return;

	auto iter = mValues.begin();
	while(iter != mValues.end() && keynum > 0){
		iter++;
		keynum--;
	}
	mValues.erase(iter);
	notifyObservers(ON_CHANGE);
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::setBounds(T bottom, T upper){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(bottom >= upper) return;
	mBottomBound = bottom;
	mUpperBound = upper;
	for(auto iter = mValues.begin(); iter != mValues.end(); iter++){
		if(iter->second < mBottomBound) iter->second = mBottomBound;
		else if(iter->second > mUpperBound) iter->second = mUpperBound;
	}
	notifyObservers(ON_CHANGE);
	return;
}

template<typename T>
const char *SimpleKeyableProperty<T>::getBottomBoundsString() const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return to_chararray(mBottomBound);
}

template<typename T>
const char *SimpleKeyableProperty<T>::getUpperBoundsString() const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return to_chararray(mUpperBound);
}

template<typename T>
std::vector<std::string> SimpleKeyableProperty<T>::getBoundsString() const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	return std::vector<std::string>{std::to_string(mBottomBound), std::to_string(mUpperBound)};
}

template<typename T>
std::vector<T> SimpleKeyableProperty<T>::getBounds() const{
	return std::vector<T>{mBottomBound, mUpperBound};
}

template<typename T>
T SimpleKeyableProperty<T>::getElement(unsigned int pos) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	auto iter = mValues.begin();
	while(iter != mValues.end() && pos > 0){
		iter++;
		pos--;
	}
	return iter->second;
}

template<typename T>
T SimpleKeyableProperty<T>::interpolate(long double pos) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	T best = mValues.begin()->second;
	for(auto iter = mValues.begin(); iter != mValues.end(); iter++){
		if(iter->first <= pos){
			best = iter->second;
		}
		else{
			iter--;
			long double pos1 = fabs(iter->first - pos);
			iter++;
			long double pos2 = fabs(iter->first - pos);
			long double div = pos1 + pos2;
			pos1 = 1 - (pos1 / div);
			pos2 = 1 - (pos2 / div);
			T next = iter->second;
			best = best * pos1 + next * pos2;
			return best;
		}
	}
	return best;
}

template<typename T>
void SimpleKeyableProperty<T>::serialize(IMultiLevelStore *data) const{
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(!data) return;
	data->add("name", mName.c_str());
	for(auto iter = mValues.begin(); iter != mValues.end(); iter++){
		data->add("value", std::to_string(iter->second).append(" ").append(std::to_string(iter->first)).c_str());
	}
	data->add("bottombound", std::to_string(mBottomBound).c_str());
	data->add("upperbound", std::to_string(mUpperBound).c_str());
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::deserialize(const IMultiLevelStore *data){
	std::lock_guard<std::recursive_mutex> lock(mMutex);
	if(!data) return;
	try{
		mName = data->get("name");
		mValues.clear();
		for(unsigned int i = 0; i < data->getSize("value"); i++){
			std::string tmp(data->get("value", i));
			std::string value = tmp.substr(0, tmp.find_first_of(' '));
			long double pos = string_to<long double>(tmp.substr(tmp.find_first_of(' ') + 1, tmp.size()));
			addKey(value.c_str(), pos);
		}
		mBottomBound = string_to<T>(std::string(data->get("bottombound")));
		mUpperBound = string_to<T>(std::string(data->get("upperbound")));
	}
	catch(std::exception &e){
		throw e;
	}
	return;
}

} // maudio

#endif // MAUDIO_SIMPLEKEYABLEPROPERTY




