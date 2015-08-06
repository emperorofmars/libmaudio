/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IPROPERTYMANAGER
#define MAUDIO_IPROPERTYMANAGER

#include "core/property/Property.hpp"
#include "core/property/KeyableProperty.hpp"

namespace maudio{

class IPropertyManager{
public:
	virtual ~IPropertyManager(){};

	virtual void add(Property *prop) = 0;
	virtual void add(KeyableProperty *prop) = 0;

	virtual bool PropertyExists(const char *name) = 0;
	virtual bool KeyablePropertyExists(const char *name) = 0;

	virtual Property *getProperty(unsigned int i) = 0;
	virtual Property *getProperty(const char *name) = 0;
	virtual KeyableProperty *getKeyableProperty(unsigned int i) = 0;
	virtual KeyableProperty *getKeyableProperty(const char *name) = 0;

	virtual void removeProperty(unsigned int i) = 0;
	virtual void removeProperty(const char *name) = 0;
	virtual void removeKeyableProperty(unsigned int i) = 0;
	virtual void removeKeyableProperty(const char *name) = 0;

	virtual unsigned int getNumProperties() const = 0;
	virtual unsigned int getNumKeyableProperties() const = 0;
};

} // maudio

#endif // MAUDIO_IPROPERTYMANAGER




