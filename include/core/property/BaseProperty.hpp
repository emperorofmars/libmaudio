/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_BASEPROPERTY
#define MAUDIO_BASEPROPERTY

#include "core/property/Property.hpp"

namespace maudio{

template<typename T>
class BaseProperty : public Property{
public:
	BaseProperty(const std::string &name, T value);
	virtual ~BaseProperty();

	virtual std::string getString() const;
	virtual T get() const;
	virtual void set(const std::string &value);
	virtual void set(const char *value);
	virtual void set(T value);

	virtual std::string getBounds() const;

private:
	T mValue;
};

typedef BaseProperty<bool> BoolProperty;
typedef BaseProperty<int> IntProperty;
typedef BaseProperty<unsigned int> UIntProperty;
typedef BaseProperty<long> LongProperty;
typedef BaseProperty<unsigned long> ULongProperty;
typedef BaseProperty<float> FloatProperty;
typedef BaseProperty<double> DoubleProperty;
typedef BaseProperty<std::string> StringProperty;

template<typename T>
BaseProperty<T>::BaseProperty(const std::string &name, T value)
	:Property(name)
{
	set(value);
}

template<typename T>
BaseProperty<T>::~BaseProperty(){
}

template<typename T>
T BaseProperty<T>::get() const{
	return mValue;
}

template<typename T>
void BaseProperty<T>::set(const char *value){
	set(std::string(value));
	return;
}

template<typename T>
void BaseProperty<T>::set(T value){
	mValue = value;
	return;
}

template<typename T>
std::string BaseProperty<T>::getBounds() const{
	return "none";
}

} // maudio

#endif // MAUDIO_BASEPROPERTY




