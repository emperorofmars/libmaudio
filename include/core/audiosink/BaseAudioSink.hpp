/*
 * INode specialisation for AudioSinks
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BASEAUDIOSINK
#define MAUDIO_BASEAUDIOSINK

#include "core/node/Node.hpp"

namespace maudio{

class BaseAudioSink : public Node{
public:
	virtual ~BaseAudioSink();

	virtual Sample get(unsigned long pos) noexcept final;
	virtual AudioInfo getInfo() noexcept;
    virtual int MaxInputs() const final;
    virtual bool HasOutputs() const final;
};

} // maudio

#endif // MAUDIO_BASEAUDIOSINK


