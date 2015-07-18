/*
 * INode specialisation for AudioSource
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BASEAUDIOSOURCE
#define MAUDIO_BASEAUDIOSOURCE

#include "core/node/BaseNode.hpp"

namespace maudio{

class BaseAudioSource : public BaseNode{
public:
	virtual ~BaseAudioSource();

    virtual int getMaxInput() final;
};

} // maudio

#endif // MAUDIO_BASEAUDIOSOURCE


