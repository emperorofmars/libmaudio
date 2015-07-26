/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SIMPLEKEYABLEPROPERTY
#define MAUDIO_SIMPLEKEYABLEPROPERTY

#include "core/property/KeyableProperty.hpp"
#include "core/util/Util.hpp"
#include <vector>
#include <limits>
#include <map>
#include <cmath>

namespace maudio{

template<typename T>
class SimpleKeyableProperty : public KeyableProperty{
public:
    SimpleKeyableProperty(const std::string &name, T initialValue);
    virtual ~SimpleKeyableProperty();

    virtual std::string getString(long double pos) const;
    virtual T get(long double pos) const;
    virtual std::string getKeyString(unsigned int keynum) const;
    virtual T get(unsigned int keynum) const;
    virtual unsigned int getNumKeys() const;
    virtual void addKey(const std::string &value, long double pos);
    virtual void addKey(T value, long double pos);
	virtual void addKey(const char *value, long double pos);
    virtual void setKey(const std::string &value, unsigned int keynum);
    virtual void setKey(T value, unsigned int keynum);
	virtual void setKey(const char *value, unsigned int keynum);
    virtual void removeKey(unsigned int keynum);

	virtual void setBounds(T bottom, T upper);
	virtual std::vector<std::string> getBoundsString() const;
	virtual std::vector<T> getBounds() const;

private:
	unsigned int getClosest(long double pos);

    std::string mName;
    std::map<std::string, T> mValues;
	T mBottomBound;
	T mUpperBound;
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
SimpleKeyableProperty<T>::SimpleKeyableProperty(const std::string &name, T value)
	:KeyableProperty(name)
{
	set(value, 0);
	mBottomBound = std::numeric_limits<T>::min();
	mUpperBound = std::numeric_limits<T>::max();
}

template<typename T>
SimpleKeyableProperty<T>::~SimpleKeyableProperty(){
}

template<typename T>
std::string SimpleKeyableProperty<T>::getString(long double pos) const{
	return std::to_string(mValues[getClosest(pos)]);
}

template<typename T>
T SimpleKeyableProperty<T>::get(long double pos) const{
	//TODO: interpolate
	return mValues[getClosest(pos)];
}

template<typename T>
std::string SimpleKeyableProperty<T>::getKeyString(unsigned int keynum) const{
	return std::to_string(mValues.begin() + keynum);
}

template<typename T>
T SimpleKeyableProperty<T>::get(unsigned int keynum) const{
	return mValues[mValues.begin() + keynum];
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
	}
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::addKey(T value, long double pos){
	if(value < mBottomBound) value = mBottomBound;
	else if(value > mUpperBound) value = mUpperBound;
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
	}
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::setKey(T value, unsigned int keynum){
	if(keynum >= mValues.size()) return;
	if(value < mBottomBound) value = mBottomBound;
	else if(value > mUpperBound) value = mUpperBound;

	auto iter = mValues.begin() + keynum;
	iter->second = value;
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::setKey(const char *value, unsigned int keynum){
	setKey(std::string(value), keynum);
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::removeKey(unsigned int keynum){
	if(mValues.size() <= 1) return;
	if(keynum >= mValues.size()) return;
	mValues.erase(mValues.begin() + keynum);
	return;
}

template<typename T>
void SimpleKeyableProperty<T>::setBounds(T bottom, T upper){
	if(bottom >= upper) return;
	mBottomBound = bottom;
	mUpperBound = upper;
	return;
}

template<typename T>
std::vector<std::string> SimpleKeyableProperty<T>::getBoundsString() const{
	return std::vector<std::string>{std::to_string(mBottomBound), std::to_string(mUpperBound)};
}

template<typename T>
std::vector<T> SimpleKeyableProperty<T>::getBounds() const{
	return std::vector<T>{mBottomBound, mUpperBound};
}

template<typename T>
unsigned int SimpleKeyableProperty<T>::getClosest(long double pos){
	unsigned int best = 0;
	long double dist = pos;
	for(auto iter = mValues.begin(); iter != mValues.end(); iter++){
		if(fabs(pos - (iter)->first) < dist){
			dist = fabs(pos - (iter)->first);
			best++;
		}
		else return best;
	}
	return 0;
}

} // maudio

#endif // MAUDIO_SIMPLEKEYABLEPROPERTY




