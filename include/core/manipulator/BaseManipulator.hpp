/*
 * INode specialisation for Manipulating Audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_BASEMANIPULATOR
#define MAUDIO_BASEMANIPULATOR

#include "core/node/BaseNode.hpp"

namespace maudio{

class BaseManipulator : public BaseNode{
public:
	virtual ~BaseManipulator();

};

} // maudio

#endif // MAUDIO_BASEMANIPULATOR


