/*
 * Interface for Nodes
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_INODE
#define MAUDIO_INODE

#include "core/util/UniqueID.hpp"
#include "core/node/Edge.hpp"
#include "core/audiodata/Sample.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <vector>
#include <memory>

namespace maudio{

class INode : public std::enable_shared_from_this<INode>, public UniqueID{
public:
	virtual ~INode(){};

	virtual Sample get(unsigned long pos) = 0;
	virtual AudioInfo getAudioInfo() = 0;

	virtual void addInput(std::shared_ptr<INode> node, int inputSlot) = 0;
	virtual void removeInput(std::shared_ptr<INode> node) = 0;
	virtual void removeInput(int inputSlot) = 0;
    virtual std::shared_ptr<INode> getInput(int inputSlot) = 0;
    virtual std::shared_ptr<INode> getByID(unsigned int id) = 0;
    virtual std::vector<std::shared_ptr<INode>> getOutputs() = 0;
    virtual void disconnect() = 0;
    virtual int getNumInputs() = 0;
    virtual int getMaxInputs() = 0;
    virtual bool HasOutputs() = 0;

    virtual std::shared_ptr<Edge> getEdge(std::weak_ptr<INode> output) = 0;
    virtual bool checkCycles(std::vector<INode*> elements) = 0;
};

} // maudio

#endif // MAUDIO_INODE









