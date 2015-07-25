/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/Config.hpp"

namespace maudio{

Config::Config(){
}

Config::~Config(){
}

void Config::parseFile(const std::string &file){
    return;
}

void Config::saveFile(){
    return;
}

void Config::saveFile(const std::string &file){
    return;
}

std::string Config::get(const std::string &key){
    return "0";
}

double Config::get_double(const std::string &key){
    return 0;
}

long Config::get_long(const std::string &key){
    return 0;
}

unsigned long Config::get_ulong(const std::string &key){
    return 0;
}

void Config::set(const std::string &key, const std::string &value){
    return;
}

void Config::set(const std::string &key, double value){
    return;
}

void Config::set(const std::string &key, long value){
    return;
}

void Config::set(const std::string &key, unsigned long value){
    return;
}


} // maudio



