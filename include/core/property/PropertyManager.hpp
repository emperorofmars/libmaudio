/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PROPERTYMANAGER
#define MAUDIO_PROPERTYMANAGER

#include "core/property/Property.hpp"
#include "core/property/KeyableProperty.hpp"
#include <vector>

namespace maudio{

class PropertyManager{
public:
	PropertyManager();
	~PropertyManager();

	void add(Property &prop);
	void add(KeyableProperty &prop);

	Property& getProperty(unsigned int i);
	Property& getProperty(const std::string &name);
	KeyableProperty& getKeyableProperty(unsigned int i);
	KeyableProperty& getKeyableProperty(const std::string &name);

	unsigned int getNumProperties();
	unsigned int getNumKeyableProperties();

private:
	std::vector<Property&> mProperties;
	std::vector<KeyableProperty&> mKeyableProperties;
};

} // maudio

#endif // MAUDIO_PROPERTYMANAGER




