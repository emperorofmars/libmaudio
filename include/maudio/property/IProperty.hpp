/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IPROPERTY
#define MAUDIO_IPROPERTY

#include "maudio/util/BaseObservable.hpp"
#include "maudio/store/IMultiLevelStore.hpp"
#include "maudio/serializer/ISerializable.hpp"

namespace maudio{

class IProperty : public BaseObservable, public ISerializable{
public:
    virtual ~IProperty(){};

    virtual const char *getString() const = 0;
	virtual void set(const char *value) = 0;

    virtual const char *getName() const = 0;
	virtual const char *getBottomBoundsString() const = 0;
	virtual const char *getUpperBoundsString() const = 0;
};

} // maudio

#endif // MAUDIO_IPROPERTY




