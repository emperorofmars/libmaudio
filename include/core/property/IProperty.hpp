/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_IPROPERTY
#define MAUDIO_IPROPERTY

#include "core/util/BaseObservable.hpp"
#include "core/store/IMultiLevelStore.hpp"

namespace maudio{

class IProperty : public BaseObservable{
public:
    virtual ~IProperty(){};

    virtual const char *getString() const = 0;
	virtual void set(const char *value) = 0;

    virtual const char *getName() const = 0;
	virtual const char *getBottomBoundsString() const = 0;
	virtual const char *getUpperBoundsString() const = 0;
/*
	virtual IMultiLevelStore *serialize() const = 0;
	virtual void deserialize(const IMultiLevelStore *data) = 0;
*/
};

} // maudio

#endif // MAUDIO_IPROPERTY




