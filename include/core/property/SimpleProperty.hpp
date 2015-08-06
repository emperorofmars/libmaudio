/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SIMPLEPROPERTY
#define MAUDIO_SIMPLEPROPERTY

#include "core/property/IProperty.hpp"
#include "core/util/Util.hpp"
#include "core/util/AudioException.hpp"
#include <vector>
#include <limits>

namespace maudio{

template<typename T>
class SimpleProperty : public IProperty{
public:
	SimpleProperty(const char *name, T value);
	virtual ~SimpleProperty();

    virtual const char *getName() const;
    virtual const char *getString() const;
	virtual T get() const;
	virtual void set(const std::string &value);
	virtual void set(const char *value);
	virtual void set(T value);

	virtual void setBounds(T bottom, T upper);
	virtual const char *getBottomBoundsString() const;
	virtual const char *getUpperBoundsString() const;
	virtual std::vector<std::string> getBoundsString() const;
	virtual std::vector<T> getBounds() const;

private:
	std::string mName;
	T mValue;
	T mBottomBound;
	T mUpperBound;
};

typedef SimpleProperty<bool> BoolProperty;
typedef SimpleProperty<int> IntProperty;
typedef SimpleProperty<unsigned int> UIntProperty;
typedef SimpleProperty<long> LongProperty;
typedef SimpleProperty<unsigned long> ULongProperty;
typedef SimpleProperty<float> FloatProperty;
typedef SimpleProperty<double> DoubleProperty;
typedef SimpleProperty<std::string> StringProperty;

template<typename T>
SimpleProperty<T>::SimpleProperty(const char *name, T value){
	mName = std::string(name);
	mBottomBound = std::numeric_limits<T>::min();
	mUpperBound = std::numeric_limits<T>::max();
	set(value);
}

template<typename T>
SimpleProperty<T>::~SimpleProperty(){
}

template<typename T>
const char *SimpleProperty<T>::getName() const{
	return mName.c_str();
}

template<typename T>
const char *SimpleProperty<T>::getString() const{
	return to_chararray(mValue);
}

template<typename T>
T SimpleProperty<T>::get() const{
	return mValue;
}

template<typename T>
void SimpleProperty<T>::set(const std::string &value){
	try{set(string_to<T>(value));}
	catch(std::exception &e){
		throw MaudioException("failed to set value");
	}
	return;
}

template<typename T>
void SimpleProperty<T>::set(const char *value){
	set(std::string(value));
	return;
}

template<typename T>
void SimpleProperty<T>::set(T value){
	if(value < mBottomBound) mValue = mBottomBound;
	else if(value > mUpperBound) mValue = mUpperBound;
	else mValue = value;
	return;
}

template<typename T>
void SimpleProperty<T>::setBounds(T bottom, T upper){
	if(bottom >= upper) return;
	mBottomBound = bottom;
	mUpperBound = upper;
	return;
}

template<typename T>
const char *SimpleProperty<T>::getBottomBoundsString() const{
	return to_chararray(mBottomBound);
}

template<typename T>
const char *SimpleProperty<T>::getUpperBoundsString() const{
	return to_chararray(mUpperBound);
}

template<typename T>
std::vector<std::string> SimpleProperty<T>::getBoundsString() const{
	return std::vector<std::string>{std::to_string(mBottomBound), std::to_string(mUpperBound)};
}

template<typename T>
std::vector<T> SimpleProperty<T>::getBounds() const{
	return std::vector<T>{mBottomBound, mUpperBound};
}

} // maudio

#endif // MAUDIO_SIMPLEPROPERTY




