/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IKEYABLEPROPERTY
#define MAUDIO_IKEYABLEPROPERTY

#include "maudio/util/BaseObservable.hpp"
#include "maudio/store/IMultiLevelStore.hpp"
#include "maudio/serializer/ISerializable.hpp"

namespace maudio{

class IKeyableProperty : public BaseObservable, public ISerializable{
public:
	virtual ~IKeyableProperty(){};

	virtual const char *getName() const = 0;

	virtual const char *getString(long double pos) const = 0;
	virtual const char *getKeyString(unsigned int keynum) const = 0;
	virtual long double getKeyPos(unsigned int keynum) const = 0;
	virtual unsigned int getNumKeys() const = 0;
	virtual void addKey(const char *value, long double pos) = 0;
	virtual void setKey(const char *value, unsigned int keynum) = 0;
	virtual void removeKey(unsigned int keynum) = 0;

	virtual const char *getBottomBoundsString() const = 0;
	virtual const char *getUpperBoundsString() const = 0;
};

} // maudio

#endif // MAUDIO_IKEYABLEPROPERTY




