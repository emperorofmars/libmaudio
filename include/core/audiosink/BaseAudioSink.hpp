/*
 * INode specialisation for AudioSinks
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BASEAUDIOSINK
#define MAUDIO_BASEAUDIOSINK

#include "core/node/BaseNode.hpp"

namespace maudio{

class BaseAudioSink : public BaseNode{
public:
	virtual ~BaseAudioSink();

	virtual Sample get(unsigned long pos) final;
	virtual AudioInfo getAudioInfo();
    virtual int getMaxInputs() final;

    virtual std::shared_ptr<Edge> getEdge(std::weak_ptr<INode> output) final;

protected:
	std::vector<std::shared_ptr<INode>> mNodes;
};

} // maudio

#endif // MAUDIO_BASEAUDIOSINK


