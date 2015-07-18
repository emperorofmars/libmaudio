/*
 * INode specialisation for AudioSinks
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BASEAUDIOSINK
#define MAUDIO_BASEAUDIOSINK

#include "core/node/INode.hpp"

namespace maudio{

class BaseAudioSink : public INode{
public:
	virtual ~BaseAudioSink();

    virtual Sample get(unsigned long pos, int output);
	virtual void addNode(std::shared_ptr<INode> node, int inputPos = 0);
	virtual void removeNode(std::shared_ptr<INode> node);
	virtual void removeNode(int inputPos);
    virtual std::vector<std::shared_ptr<INode>> getNodes();
    virtual int getMaxInput() final;

protected:
	std::vector<std::shared_ptr<INode>> mNodes;
};

} // maudio

#endif // MAUDIO_BASEAUDIOSINK


