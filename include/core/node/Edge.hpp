/*
 * Interface for Nodes
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_EDGE
#define MAUDIO_EDGE

#include <memory>

namespace maudio{

class INode;

class Edge{
public:
	Edge(std::shared_ptr<INode> input, std::weak_ptr<INode> output);
	~Edge();

	bool valid();
	void expire();
	std::shared_ptr<INode> getInput();
	std::shared_ptr<INode> getOutput();

private:
	std::shared_ptr<INode> mInput;
	std::weak_ptr<INode> mOutput;
};

} // maudio

#endif // MAUDIO_EDGE









