/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ERRORACTION
#define MAUDIO_ERRORACTION

#include "core/action/BaseAction.hpp"

namespace maudio{

class ErrorAction : public BaseAction{
public:
	ErrorAction();
	virtual ~ErrorAction();
	
	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept;
	virtual IAudioInfo *getInfo() noexcept;

	virtual int MaxInputs() const;
	virtual bool HasOutputs() const;

	virtual void readConfig(const IKeyValueStore *conf);

	virtual void serialize(IMultiLevelStore *data) const;
	virtual void deserialize(const IMultiLevelStore *data);
};

} // maudio

#endif // MAUDIO_ERRORACTION




