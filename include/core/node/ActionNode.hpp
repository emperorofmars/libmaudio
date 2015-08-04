/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ACTIONNODE
#define MAUDIO_ACTIONNODE

#include "core/node/Node.hpp"
#include "core/node/IAction.hpp"
#include "core/node/ISocket.hpp"

namespace maudio{

class ActionNode : public Node{
public:
	ActionNode(IAction *action);
	ActionNode(std::unique_ptr<IAction> action);
	virtual ~ActionNode();

	virtual std::shared_ptr<IAudioBuffer> get(unsigned long pos, unsigned int length) noexcept;
	virtual std::shared_ptr<IAudioInfo> getInfo() noexcept;

	virtual int MaxInputs() const;
	virtual bool HasOutputs() const;

	virtual void readConfig(const Config &conf);

	virtual PropertyManager *getProperties();

	//virtual KeyValueStore serialize() const;
	//virtual void unserialize(const KeyValueStore &data);

protected:

	virtual void onAdd(unsigned int slot);
	virtual void onRemove(unsigned int slot);

	class Socket : public ISocket{
		public:
			Socket(std::shared_ptr<Node> input);
			virtual ~Socket();

			virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept;
			virtual IAudioInfo *getInfo() noexcept;

		private:
			std::shared_ptr<Node> mInput;
	};

	std::unique_ptr<IAction> mAction;
};

} // maudio

#endif // MAUDIO_ACTIONNODE









