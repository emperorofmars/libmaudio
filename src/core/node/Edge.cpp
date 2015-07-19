/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/node/Edge.hpp"

namespace maudio{

Edge::Edge(std::shared_ptr<INode> input, std::weak_ptr<INode> output){
	mInput = input;
	mOutput = output;
}

Edge::~Edge(){
}

bool Edge::valid(){
	if(mInput || !mOutput.expired()) return true;
	return false;
}

void Edge::expire(){
	mInput.reset();
	mOutput.reset();
}

std::shared_ptr<INode> Edge::getInput(){
	return mInput;
}

std::shared_ptr<INode> Edge::getOutput(){
	return mOutput.lock();
}

} // maudio






