/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */


#ifndef MAUDIO_BASEMANIPULATOR
#define MAUDIO_BASEMANIPULATOR

#include "core/node/Node.hpp"

namespace maudio{

class BaseManipulator : public Node{
public:
	virtual ~BaseManipulator();

    virtual bool HasOutputs() const final;

	virtual void onAdd(unsigned int slot);
	virtual void onRemove(unsigned int slot);
};

} // maudio

#endif // MAUDIO_BASEMANIPULATOR


