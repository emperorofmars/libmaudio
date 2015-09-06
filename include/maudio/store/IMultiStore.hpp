/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IMULTISTORE
#define MAUDIO_IMULTISTORE

namespace maudio{

class IMultiStore{
public:
	virtual ~IMultiStore(){};

	virtual const char *get(const char *key, unsigned int numElm = 0) const = 0;
	virtual const char *get(unsigned int numKey) const = 0;
	virtual const char *getKey(unsigned int numKey) const = 0;
	virtual unsigned int getSize() const = 0;
	virtual unsigned int getSize(const char *key) const = 0;
	virtual void add(const char *key, const char *value) = 0;
};

} // maudio

#endif // MAUDIO_IMULTISTORE




