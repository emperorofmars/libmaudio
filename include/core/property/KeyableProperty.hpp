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
    virtual long double getKeyPos(unsigned int keynum) const = 0;
    virtual unsigned int getNumKeys() const = 0;
    virtual void addKey(const std::string &value, long double pos) = 0;
    virtual void setKey(const std::string &value, unsigned int keynum) = 0;
    virtual void removeKey(unsigned int keynum) = 0;
    virtual void addKey(const char *value, long double pos) = 0;
    virtual void setKey(const char *value, unsigned int keynum) = 0;

    std::string getName() const;
	virtual std::vector<std::string> getBoundsString() const = 0;

	//virtual std::string serialize() const;
	//virtual void unserialize(const std::string &data);

private:
    std::string mName;
};

} // maudio

#endif // MAUDIO_KEYABLEPROPERTY




