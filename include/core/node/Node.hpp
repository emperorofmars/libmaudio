/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_NODE
#define MAUDIO_NODE

#include "core/util/UniqueID.hpp"
#include "core/audiodata/AudioBuffer.hpp"
#include "core/audiodata/AudioInfo.hpp"
#include "core/property/Property.hpp"
#include "core/property/KeyableProperty.hpp"
#include "core/property/PropertyManager.hpp"
#include "core/util/Config.hpp"
#include <vector>
#include <memory>

namespace maudio{

class Node : public std::enable_shared_from_this<Node>, public UniqueID{
public:
	virtual ~Node();

	virtual AudioBuffer get(unsigned long pos, unsigned int length) noexcept = 0;
	virtual AudioInfo getInfo() noexcept = 0;

	void addInput(std::shared_ptr<Node> node, int slot = -1);
	void removeInput(std::shared_ptr<Node> node);
	void removeInput(int slot);
	std::shared_ptr<Node> getInput(int slot);
	std::shared_ptr<Node> getOutput(int slot);
	std::shared_ptr<Node> getByID(unsigned int id);
	void disconnect();
	int unsigned NumInputs() const;
	int unsigned NumOutputs() const;

	virtual int MaxInputs() const = 0;
	virtual bool HasOutputs() const = 0;

	virtual bool checkIfCompatible(std::shared_ptr<Node> node, int slot = -1) = 0;

	virtual void readConfig(const Config &conf) = 0;

	PropertyManager getProperties();

protected:
	AudioBuffer getFromSlot(unsigned long pos, unsigned int length, unsigned int slot) noexcept;
	AudioInfo getInfoFromSlot(unsigned int slot) noexcept;

	bool checkInput(unsigned int slot) noexcept;

	virtual void onAdd(unsigned int slot) = 0;
	virtual void onRemove(unsigned int slot) = 0;

	PropertyManager mProperties;

private:
	bool checkCycles(std::shared_ptr<Node> node);
	bool checkCyclesDeep(std::vector<std::shared_ptr<Node>> nodes);

	std::vector<std::shared_ptr<Node>> mInputs;
	std::vector<std::weak_ptr<Node>> mOutputs;
};

} // maudio

#endif // MAUDIO_NODE









