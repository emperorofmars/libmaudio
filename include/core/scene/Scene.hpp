/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SCENE
#define MAUDIO_SCENE

#include "core/serializer/ISerializable.hpp"
#include "core/util/BaseObservable.hpp"
#include "core/util/sptr.hpp"
#include <string>
#include <map>

namespace maudio{

class Scene : public ISerializable, public BaseObservable{
public:
	Scene(const char *name);
	~Scene();

	void setName(const char *name);
	const char *getName();

	long addNode(sptr<IAction> node);
	void removeNode(unsigned long id);
	sptr<IAction> getEnd(unsigned long num);
	sptr<IAction> getNode(unsigned long id);

	void connect(unsigned long source, unsigned long sink);
	void disconnect(unsigned long source, unsigned long sink);

private:
	bool isPartOfScene(unsigned long id);


	std::string mName;
	std::map<unsigned long, sptr<IAction>> mNodes;
	std::unordered_map<unsigned long, std::vector<unsigned long>> mAdjacencyList;
};

} // maudio

#endif // MAUDIO_SCENE




