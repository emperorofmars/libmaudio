/*
 * INode specialisation for Manipulating Audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/manipulator/BaseManipulator.hpp"

namespace maudio{

BaseManipulator::~BaseManipulator(){
}

bool BaseManipulator::HasOutputs(){
	return true;
}

} // maudio



