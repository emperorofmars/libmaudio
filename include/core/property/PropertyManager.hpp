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
#include <memory>

namespace maudio{

class PropertyManager{
public:
	PropertyManager();
	~PropertyManager();

	void add(std::shared_ptr<Property> prop);
	void add(std::shared_ptr<KeyableProperty> prop);

	bool PropertyExists(const std::string &name);
	bool KeyablePropertyExists(const std::string &name);

	std::shared_ptr<Property> getProperty(unsigned int i);
	std::shared_ptr<Property> getProperty(const std::string &name);
	std::shared_ptr<KeyableProperty> getKeyableProperty(unsigned int i);
	std::shared_ptr<KeyableProperty> getKeyableProperty(const std::string &name);

	void removeProperty(unsigned int i);
	void removeProperty(const std::string &name);
	void removeKeyableProperty(unsigned int i);
	void removeKeyableProperty(const std::string &name);

	unsigned int getNumProperties() const;
	unsigned int getNumKeyableProperties() const;

private:
	std::vector<std::shared_ptr<Property>> mProperties;
	std::vector<std::shared_ptr<KeyableProperty>> mKeyableProperties;
};

} // maudio

#endif // MAUDIO_PROPERTYMANAGER




