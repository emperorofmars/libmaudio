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
    void saveFile();
    void saveFile(const std::string &file);

    std::string get(const std::string &key);
    double get_double(const std::string &key);
    long get_long(const std::string &key);
    unsigned long get_ulong(const std::string &key);

    void set(const std::string &key, const std::string &value);
    void set(const std::string &key, double value);
    void set(const std::string &key, long value);
    void set(const std::string &key, unsigned long value);

private:
    std::string mFile;
    std::unordered_map<std::string, std::string> mData;
};

} // maudio

#endif // MAUDIO_CONFIG









