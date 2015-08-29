/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SCENE
#define MAUDIO_SCENE

#include "core/node/Node.hpp"
#include "core/serializer/ISerializable.hpp"
#include <memory>
#include <string>

namespace maudio{

class Scene : public ISerializable, public BaseObservable{
public:
	Scene(const char *name);
	~Scene();

	void setName(const char *name);
	const char *getName();

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




