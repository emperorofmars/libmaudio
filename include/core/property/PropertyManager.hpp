/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PROPERTYMANAGER
#define MAUDIO_PROPERTYMANAGER

#include "core/property/IPropertyManager.hpp"
#include <vector>

namespace maudio{

class PropertyManager : public IPropertyManager{
public:
	PropertyManager();
	virtual ~PropertyManager();

	virtual void add(Property *prop);
	virtual void add(KeyableProperty *prop);

	virtual bool PropertyExists(const char *name);
	virtual bool KeyablePropertyExists(const char *name);

	virtual Property *getProperty(unsigned int i);
	virtual Property *getProperty(const char *name);
	virtual KeyableProperty *getKeyableProperty(unsigned int i);
	virtual KeyableProperty *getKeyableProperty(const char *name);

	virtual void removeProperty(unsigned int i);
	virtual void removeProperty(const char *name);
	virtual void removeKeyableProperty(unsigned int i);
	virtual void removeKeyableProperty(const char *name);

	virtual unsigned int getNumProperties() const;
	virtual unsigned int getNumKeyableProperties() const;

private:
	std::vector<Property *> mProperties;
	std::vector<KeyableProperty *> mKeyableProperties;
};

} // maudio

#endif // MAUDIO_PROPERTYMANAGER




