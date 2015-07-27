/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/audiosink/Performance.hpp"
#include "core/util/AudioException.hpp"
#include <iostream>
#include <chrono>

namespace maudio{

Performance::Performance(){
}

Performance::~Performance(){
}

AudioInfo Performance::getInfo() noexcept{
    AudioInfo ret;
    if(NumInputs() > 0) return getInfoFromSlot(0);
    return ret;
}

void Performance::readConfig(const Config &conf){
    return;
}

void Performance::measure(unsigned long length, unsigned int buflen){
    if(NumInputs() == 0){
        std::cout << "invalid or no Input" << std::endl;
        return;
    }
    double val = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(unsigned int i = 0; i < length; i += buflen){
        if(i + buflen > length) buflen -= i + buflen - length;
        AudioBuffer tmp = getFromSlot(i, buflen, 0);
        for(unsigned int j = 0; j < buflen; j++){
            val += tmp.get(j).get(0);
        }
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "Buffer size: " << buflen << ", total Samples: " << length << ", ";
    std::cout << "Time used: " << time << "us, " << time / 1000000 << "s, Final value: " << val << std::endl;
    return;
}

} // maudio







