/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_BASEAUDIOSINK
#define MAUDIO_BASEAUDIOSINK

#include "core/node/Node.hpp"

namespace maudio{

class BaseAudioSink : public Node{
public:
	virtual ~BaseAudioSink();

	virtual AudioBuffer get(unsigned long pos, unsigned int length) noexcept final;
	virtual AudioInfo getInfo() noexcept;
    virtual int MaxInputs() const final;
    virtual bool HasOutputs() const final;
	virtual bool checkIfCompatible(std::shared_ptr<Node> node, int slot = -1);
};

} // maudio

#endif // MAUDIO_BASEAUDIOSINK


