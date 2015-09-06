/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PROPERTYMANAGER
#define MAUDIO_PROPERTYMANAGER

#include "maudio/property/IPropertyManager.hpp"
#include <vector>

namespace maudio{

class PropertyManager : public IPropertyManager{
public:
	PropertyManager();
	virtual ~PropertyManager();

	virtual void add(IProperty *prop);
	virtual void add(IKeyableProperty *prop);

	virtual bool PropertyExists(const char *name);
	virtual bool KeyablePropertyExists(const char *name);

	virtual IProperty *getProperty(unsigned int i);
	virtual IProperty *getProperty(const char *name);
	virtual IKeyableProperty *getKeyableProperty(unsigned int i);
	virtual IKeyableProperty *getKeyableProperty(const char *name);

	virtual void removeProperty(unsigned int i);
	virtual void removeProperty(const char *name);
	virtual void removeKeyableProperty(unsigned int i);
	virtual void removeKeyableProperty(const char *name);

	virtual unsigned int getNumProperties() const;
	virtual unsigned int getNumKeyableProperties() const;

private:
	std::vector<IProperty *> mProperties;
	std::vector<IKeyableProperty *> mKeyableProperties;
};

} // maudio

#endif // MAUDIO_PROPERTYMANAGER




