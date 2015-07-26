/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SIMPLEPROPERTY
#define MAUDIO_SIMPLEPROPERTY

#include "core/property/Property.hpp"
#include "core/util/Util.hpp"
#include <vector>
#include <limits>

namespace maudio{

template<typename T>
class SimpleProperty : public Property{
public:
	SimpleProperty(const std::string &name, T value);
	virtual ~SimpleProperty();

	virtual std::string getString() const;
	virtual T get() const;
	virtual void set(const std::string &value);
	virtual void set(const char *value);
	virtual void set(T value);

	virtual void setBounds(T bottom, T upper);
	virtual std::vector<std::string> getBoundsString() const;
	virtual std::vector<T> getBounds() const;

private:
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
SimpleProperty<T>::SimpleProperty(const std::string &name, T value)
	:Property(name)
{
	set(value);
	mBottomBound = std::numeric_limits<T>::min();
	mUpperBound = std::numeric_limits<T>::max();
}

template<typename T>
SimpleProperty<T>::~SimpleProperty(){
}

template<typename T>
std::string SimpleProperty<T>::getString() const{
	return std::to_string(mValue);
}

template<typename T>
T SimpleProperty<T>::get() const{
	return mValue;
}

template<typename T>
void SimpleProperty<T>::set(const std::string &value){
	try{set(string_to<T>(value));}
	catch(std::exception &e){
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
std::vector<std::string> SimpleProperty<T>::getBoundsString() const{
	return std::vector<std::string>{std::to_string(mBottomBound), std::to_string(mUpperBound)};
}

template<typename T>
std::vector<T> SimpleProperty<T>::getBounds() const{
	return std::vector<T>{mBottomBound, mUpperBound};
}

} // maudio

#endif // MAUDIO_SIMPLEPROPERTY




