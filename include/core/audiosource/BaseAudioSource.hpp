/*
 * INode specialisation for AudioSource
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BASEAUDIOSOURCE
#define MAUDIO_BASEAUDIOSOURCE

#include "core/node/Node.hpp"

namespace maudio{

class BaseAudioSource : public Node{
public:
	virtual ~BaseAudioSource();

    virtual int MaxInputs() const final;
    virtual bool HasOutputs() const final;
};

} // maudio

#endif // MAUDIO_BASEAUDIOSOURCE


