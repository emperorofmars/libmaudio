/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_NODE
#define MAUDIO_NODE

#include "core/node/IAudioGetter.hpp"
#include "core/util/UniqueID.hpp"
#include "core/audiodata/IAudioBuffer.hpp"
#include "core/audiodata/IAudioInfo.hpp"
#include "core/property/IProperty.hpp"
#include "core/property/IKeyableProperty.hpp"
#include "core/property/IPropertyManager.hpp"
#include "core/store/IKeyValueStore.hpp"
#include "core/store/IMultiLevelStore.hpp"
#include "core/node/IControl.hpp"
#include "core/serializer/ISerializable.hpp"
#include <vector>
#include <memory>

namespace maudio{

class Node : public IAudioGetter, public std::enable_shared_from_this<Node>, public UniqueID, public ISerializable, public BaseObservable{
public:
	virtual ~Node();

	void addInput(std::shared_ptr<Node> node, int slot = -1);
	void removeInput(std::shared_ptr<Node> node);
	void removeInput(int slot);
	std::shared_ptr<Node> getInput(int slot);
	std::shared_ptr<Node> getOutput(int slot);
	std::shared_ptr<Node> getByID(unsigned int id);
	void disconnect();
	virtual unsigned int NumInputs() const;
	virtual unsigned int NumOutputs() const;

	virtual int MaxInputs() const = 0;
	virtual bool HasOutputs() const = 0;

	virtual void readConfig(const IKeyValueStore &conf) = 0;

	virtual IPropertyManager *getProperties() = 0;

	virtual IControl *getControl() = 0;

	std::string getName() const;
	void setName(const std::string &name);

protected:
	virtual void onAdd(unsigned int slot) = 0;
	virtual void onRemove(unsigned int slot) = 0;

	std::string mName;

	std::vector<std::shared_ptr<Node>> mInputs;
	std::vector<std::weak_ptr<Node>> mOutputs;

private:
	void addOutput(std::weak_ptr<Node> node);
	void removeOutput(std::weak_ptr<Node> node);

	bool checkCycles(std::shared_ptr<Node> node);
	bool checkCyclesDeep(std::vector<std::shared_ptr<Node>> nodes);
};

} // maudio

#endif // MAUDIO_NODE









