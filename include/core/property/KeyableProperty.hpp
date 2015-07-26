/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_KEYABLEPROPERTY
#define MAUDIO_KEYABLEPROPERTY

#include <string>
#include <vector>

namespace maudio{

class KeyableProperty{
public:
    KeyableProperty(const std::string &name);
    virtual ~KeyableProperty();

    virtual std::string getString(long double pos) const = 0;
    virtual std::string getKeyString(unsigned int keynum) const = 0;
    virtual unsigned int getNumKeys() = 0;
    virtual void set(const std::string &value, long double pos) = 0;
	virtual void set(const char *value, long double pos) = 0;

    std::string getName() const;
	virtual std::vector<std::string> getBoundsString() const = 0;

private:
    std::string mName;
};

} // maudio

#endif // MAUDIO_KEYABLEPROPERTY




