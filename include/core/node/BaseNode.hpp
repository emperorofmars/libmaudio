/*
 * INode specialisation for Node management
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BASENODE
#define MAUDIO_BASENODE

#include "core/node/INode.hpp"

namespace maudio{

class BaseNode : public INode{
public:
	virtual ~BaseNode();

	virtual void addInput(std::shared_ptr<INode> node, int inputSlot = -1);
	virtual void removeInput(std::shared_ptr<INode> node);
	virtual void removeInput(int inputSlot);
    virtual std::shared_ptr<INode> getInput(int inputSlot);
    virtual std::shared_ptr<INode> getByID(unsigned int id);
    virtual std::vector<std::shared_ptr<INode>> getOutputs();
    virtual void disconnect();
    virtual int getNumInputs();

    virtual std::shared_ptr<Edge> getEdge(std::weak_ptr<INode> output);
    virtual bool checkCycles(std::vector<INode*> elements);

protected:
	std::vector<std::shared_ptr<Edge>> mInputs;
	std::vector<std::weak_ptr<Edge>> mOutputs;
};

} // maudio

#endif // MAUDIO_BASENODE


