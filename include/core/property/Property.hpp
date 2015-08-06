/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PROPERTY
#define MAUDIO_PROPERTY

namespace maudio{

class Property{
public:
    virtual ~Property(){};

    virtual const char *getString() const = 0;
	virtual void set(const char *value) = 0;

    virtual const char *getName() const = 0;
	virtual const char *getBottomBoundsString() const = 0;
	virtual const char *getUpperBoundsString() const = 0;

	//virtual std::string serialize() const;
	//virtual void unserialize(const std::string &data);
};

} // maudio

#endif // MAUDIO_PROPERTY




