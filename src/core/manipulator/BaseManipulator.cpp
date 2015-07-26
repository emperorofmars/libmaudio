/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/manipulator/BaseManipulator.hpp"

namespace maudio{

BaseManipulator::~BaseManipulator(){
}

bool BaseManipulator::HasOutputs() const{
	return true;
}

void BaseManipulator::onAdd(unsigned int slot){
	return;
}

void BaseManipulator::onRemove(unsigned int slot){
	return;
}

} // maudio



