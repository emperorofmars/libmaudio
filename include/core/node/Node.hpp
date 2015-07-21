/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_NODE
#define MAUDIO_NODE

#include "core/util/UniqueID.hpp"
#include "core/audiodata/Sample.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include <vector>
#include <memory>

namespace maudio{

class Node : public std::enable_shared_from_this<Node>, public UniqueID{
public:
	virtual ~Node();

	virtual Sample get(unsigned long pos) noexcept = 0;
	virtual AudioInfo getInfo() noexcept = 0;

	void addInput(std::shared_ptr<Node> node, int slot = -1);
	void removeInput(std::shared_ptr<Node> node);
	void removeInput(int slot);
	std::shared_ptr<Node> getInput(int slot);
	std::shared_ptr<Node> getOutput(int slot);
	std::shared_ptr<Node> getByID(unsigned int id);
	void disconnect();
	int NumInputs() const;
	int NumOutputs() const;

	Sample getFromSlot(unsigned int slot, unsigned long pos) noexcept;
	AudioInfo getInfoFromSlot(unsigned int slot) noexcept;

	virtual int MaxInputs() const = 0;
	virtual bool HasOutputs() const = 0;

private:
	bool checkCycles(std::vector<std::shared_ptr<Node>> nodes);

	std::vector<std::shared_ptr<Node>> mInputs;
	std::vector<std::weak_ptr<Node>> mOutputs;
};

} // maudio

#endif // MAUDIO_NODE









