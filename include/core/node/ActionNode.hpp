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

	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept;
	virtual IAudioInfo *getInfo() noexcept;

	virtual void deleteBuffer(IAudioBuffer *data) noexcept;
	virtual void deleteInfo(IAudioInfo *data) noexcept;
	virtual void deleteSample(ISample *data) noexcept;

	virtual int MaxInputs() const;
	virtual bool HasOutputs() const;

	virtual void readConfig(const IKeyValueStore &conf);

	virtual IPropertyManager *getProperties();

	virtual IControl *getControl();

	virtual IKeyValueStore *serialize() const;
	virtual void deserialize(const IKeyValueStore *data);

protected:

	virtual void onAdd(unsigned int slot);
	virtual void onRemove(unsigned int slot);

	class Socket : public ISocket{
		public:
			Socket(std::shared_ptr<Node> input);
			virtual ~Socket();

			virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept;
			virtual IAudioInfo *getInfo() noexcept;

			virtual void deleteBuffer(IAudioBuffer *data) noexcept;
			virtual void deleteInfo(IAudioInfo *data) noexcept;
			virtual void deleteSample(ISample *data) noexcept;

		private:
			std::shared_ptr<Node> mInput;
	};

	std::unique_ptr<IAction> mAction;
};

} // maudio

#endif // MAUDIO_ACTIONNODE









