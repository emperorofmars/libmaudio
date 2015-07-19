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

	virtual void addInput(std::shared_ptr<INode> node, int inputSlot);
	virtual void removeInput(std::shared_ptr<INode> node);
	virtual void removeInput(int inputSlot);
    virtual std::shared_ptr<INode> getInput(int inputSlot);
    virtual std::vector<std::shared_ptr<INode>> getOutputs();
    virtual void disconnect();

protected:
    class BaseLink : public ILink{
	public:
		BaseLink();
    	virtual ~BaseLink();

		virtual bool valid();
		virtual void expire();
    	virtual std::shared_ptr<INode> getInput();
    	virtual std::shared_ptr<INode> getOutput();
		virtual void setInput(std::shared_ptr<INode> node);
		virtual void setOutput(std::weak_ptr<INode> node);

	protected:
		std::shared_ptr<INode> mInput;
		std::weak_ptr<INode> mOutput;
    };

	std::vector<std::shared_ptr<ILink>> mInputs;
	std::vector<std::weak_ptr<ILink>> mOutputs;

public:
    virtual bool checkCycles(std::vector<INode*> elements);
};

} // maudio

#endif // MAUDIO_BASENODE


