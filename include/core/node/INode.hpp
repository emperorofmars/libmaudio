/*
 * Interface for Nodes
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_INODE
#define MAUDIO_INODE

#include "core/audiodata/Sample.hpp"
#include "core/audiodata/FileInfo.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <vector>
#include <memory>

namespace maudio{

class INode{
public:
	virtual ~INode(){};

    virtual Sample get(unsigned long pos, int output) = 0;

	virtual void addNode(std::shared_ptr<INode> node, int inputPos) = 0;
	virtual void removeNode(std::shared_ptr<INode> node) = 0;
	virtual void removeNode(int inputPos) = 0;
    virtual std::vector<std::shared_ptr<INode>> getNodes() = 0;

    virtual int getMaxInput() = 0;
    virtual AudioInfo getAudioInfo() = 0;
    virtual FileInfo getFileInfo() = 0;
};

} // maudio

#endif // MAUDIO_INODE


