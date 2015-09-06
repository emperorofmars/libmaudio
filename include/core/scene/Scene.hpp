/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SCENE
#define MAUDIO_SCENE

#include "core/serializer/ISerializable.hpp"
#include "core/util/BaseObservable.hpp"
#include "core/action/IAction.hpp"
#include "core/util/sptr.hpp"
#include <string>
#include <map>
#include <mutex>

namespace maudio{

class Scene : public ISerializable, public BaseObservable{
public:
	Scene(const char *name = "default_scene");
	~Scene();

	void setName(const char *name);
	const char *getName() const;

	long add(IAction *node);
	long add(sptr<IAction> node);
	void remove(unsigned long id);
	sptr<IAction> getEnd(unsigned int num);
	sptr<IAction> get(unsigned long id);
	
	unsigned int getNumEnds();

	void connect(unsigned long source, unsigned long sink);
	void disconnect(unsigned long source, unsigned long sink);

	std::vector<unsigned long> getOutputs(unsigned long id);
	
	virtual void readConfig(const IKeyValueStore *conf);
	
	virtual void serialize(IMultiLevelStore *data) const;
	virtual void deserialize(const IMultiLevelStore *data);
	
private:
	bool isPartOfScene(unsigned long id);

	std::string mName;
	std::map<unsigned long, sptr<IAction>> mNodes;
	std::map<unsigned long, std::vector<unsigned long>> mAdjacencyList;
	mutable std::recursive_mutex mMutex;
};

} // maudio

#endif // MAUDIO_SCENE




