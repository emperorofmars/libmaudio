/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
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

	virtual void onAdd(unsigned int slot);
	virtual void onRemove(unsigned int slot);
};

} // maudio

#endif // MAUDIO_BASEAUDIOSOURCE


