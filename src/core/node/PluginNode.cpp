/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/node/PluginNode.hpp"
#include "core/util/AudioException.hpp"

namespace maudio{

PluginNode::PluginNode(plugin_ptr<IAction> action){
	mAction.reset(action);
}

PluginNode::~PluginNode(){
}

IAudioBuffer *PluginNode::get(unsigned long pos, unsigned int length) noexcept{
	if(!mAction) return NULL;
	IAudioBuffer *ret(mAction->get(pos, length));
	return ret;
}

IAudioInfo *PluginNode::getInfo() noexcept{
	if(!mAction) return NULL;
	IAudioInfo *ret(mAction->getInfo());
	return ret;
}

void PluginNode::deleteBuffer(IAudioBuffer *data) noexcept{
	if(mAction) mAction->deleteBuffer(data);
	return;
}

void PluginNode::deleteInfo(IAudioInfo *data) noexcept{
	if(mAction) mAction->deleteInfo(data);
	return;
}

void PluginNode::deleteSample(ISample *data) noexcept{
	if(mAction) mAction->deleteSample(data);
	return;
}

int PluginNode::MaxInputs() const{
	if(!mAction) return 0;
	return mAction->MaxInputs();
}

bool PluginNode::HasOutputs() const{
	if(!mAction) return false;
	return mAction->HasOutputs();
}

void PluginNode::readConfig(const IKeyValueStore &conf){
	if(!mAction) return;
	mAction->readConfig(conf);
	return;
}

IPropertyManager *PluginNode::getProperties(){
	if(!mAction) return NULL;
	return mAction->getProperties();
}

IControl *PluginNode::getControl(){
	if(!mAction) return NULL;
	return mAction->getControl();
}

bool PluginNode::checkCompatible(IAudioInfo *info){
	return mAction->checkCompatible(info);
}

void PluginNode::onAdd(unsigned int slot){
	if(!mAction) return;
	mAction->addSocket(mInputs[slot].get(), slot);
	return;
}

void PluginNode::onRemove(unsigned int slot){
	if(!mAction) return;
	mAction->removeSocket(slot);
	return;
}

void PluginNode::serialize(IMultiLevelStore *data) const{
	return;
}

void PluginNode::deserialize(const IMultiLevelStore *data){
	return;
}

} // maudio



