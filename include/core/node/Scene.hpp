/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SCENE
#define MAUDIO_SCENE

#include "core/node/Node.hpp"
#include <memory>
#include <string>

namespace maudio{

class Scene{
public:
	Scene();
	~Scene();

	void addNode(std::shared_ptr<Node> node);
	void removeNode(unsigned long id);
	std::shared_ptr<Node> getEnd(unsigned int num);
	std::shared_ptr<Node> getNode(unsigned long id);

	void connect(unsigned long source, unsigned long sink);
	void disconnect(unsigned long source, unsigned long sink);

private:
	std::string mName;

	std::vector<std::shared_ptr<Node>> mEnds;
};

} // maudio

#endif // MAUDIO_SCENE




