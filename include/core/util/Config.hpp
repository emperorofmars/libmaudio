/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_CONFIG
#define MAUDIO_CONFIG

#include <string>
#include <unordered_map>

namespace maudio{

class Config{
public:
    Config();
    ~Config();

    void parseFile(const std::string &file);
    void saveFile() const;
    void saveFile(const std::string &file) const;

    std::string get(const std::string &key) const;
    double get_double(const std::string &key) const;
    long get_long(const std::string &key) const;
    unsigned long get_ulong(const std::string &key) const;

    void set(const std::string &key, const std::string &value);
    void set(const std::string &key, double value);
    void set(const std::string &key, long value);
    void set(const std::string &key, unsigned long value);

    void setDefaults();

private:
	bool checkKey(const std::string &key) const;
	void parseLine(std::string &line);

    std::string mFile;
    std::unordered_map<std::string, std::string> mData;
};

} // maudio

#endif // MAUDIO_CONFIG









