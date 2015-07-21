/*
 * INode specialisation for Manipulating Audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BASEMANIPULATOR
#define MAUDIO_BASEMANIPULATOR

#include "core/node/Node.hpp"

namespace maudio{

class BaseManipulator : public Node{
public:
	virtual ~BaseManipulator();

    virtual bool HasOutputs() final;
};

} // maudio

#endif // MAUDIO_BASEMANIPULATOR


