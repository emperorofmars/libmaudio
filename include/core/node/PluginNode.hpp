/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PLUGINNODE
#define MAUDIO_PLUGINNODE

#include "core/node/Node.hpp"
#include "core/node/IAction.hpp"
#include "core/node/IAudioGetter.hpp"
#include "core/util/plugin_ptr.hpp"

namespace maudio{

class PluginNode : public Node{
public:
	PluginNode(plugin_ptr<IAction> action);
	virtual ~PluginNode();

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

	virtual bool checkCompatible(IAudioInfo *info);
/*
	virtual IKeyValueStore *serialize() const;
	virtual void deserialize(const IKeyValueStore *data);
*/
protected:
	virtual void onAdd(unsigned int slot);
	virtual void onRemove(unsigned int slot);

	plugin_ptr<IAction> mAction;
};

} // maudio

#endif // MAUDIO_PLUGINNODE









