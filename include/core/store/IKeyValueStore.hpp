/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IKEYVALUESTORE
#define MAUDIO_IKEYVALUESTORE

#include <string>
#include <unordered_map>

namespace maudio{

class IKeyValueStore{
public:
	virtual ~IKeyValueStore(){};

	virtual const char *get(const char *key) const = 0;
	virtual const char *get(unsigned int numKey) const = 0;
	virtual unsigned int getSize() const = 0;
	virtual void set(const char *key, const char *value) = 0;
};

} // maudio

#endif // MAUDIO_IKEYVALUESTORE









