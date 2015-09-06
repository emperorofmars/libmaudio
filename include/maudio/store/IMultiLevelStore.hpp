/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IMULTILEVELSTORE
#define MAUDIO_IMULTILEVELSTORE

#include "maudio/store/IMultiStore.hpp"

namespace maudio{

class IMultiLevelStore : public IMultiStore{
public:
	virtual ~IMultiLevelStore(){};

	virtual const char *get(const char *key, unsigned int numElm = 0) const = 0;
	virtual const char *get(unsigned int numKey) const = 0;
	virtual const char *getKey(unsigned int numKey) const = 0;
	virtual IMultiLevelStore *getLevel(const char *key, unsigned int numElm = 0) const = 0;
	virtual IMultiLevelStore *getLevel(unsigned int numKey) const = 0;
	virtual const char *getLevelKey(unsigned int numKey) const = 0;
	virtual unsigned int getSize() const = 0;
	virtual unsigned int getSize(const char *key) const = 0;
	virtual unsigned int getNumLevels() const = 0;
	virtual unsigned int getNumLevels(const char *key) const = 0;
	virtual void add(const char *key, const char *value) = 0;
	virtual IMultiLevelStore *addLevel(const char *key) = 0;
};

} // maudio

#endif // MAUDIO_IMULTILEVELSTORE




