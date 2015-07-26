/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PROPERTY
#define MAUDIO_PROPERTY

#include <string>

namespace maudio{

class Property{
public:
    Property(const std::string &name);
    virtual ~Property();

    virtual std::string getString() const = 0;
    virtual void set(const std::string &value) = 0;
	virtual void set(const char *value) = 0;

    std::string getName() const;
	virtual std::string getBounds() const = 0;

private:
    std::string mName;
};

} // maudio

#endif // MAUDIO_PROPERTY




