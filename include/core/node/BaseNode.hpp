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

	virtual void addNode(std::shared_ptr<INode> node, int inputPos);
	virtual void removeNode(std::shared_ptr<INode> node);
	virtual void removeNode(int inputPos);
    virtual std::vector<std::shared_ptr<INode>> getNodes();

protected:
	std::vector<std::shared_ptr<INode>> mNodes;
};

} // maudio

#endif // MAUDIO_BASENODE


