/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ISERIALIZER
#define MAUDIO_ISERIALIZER

#include "maudio/scene/Scene.hpp"
#include <memory>
#include <vector>

namespace maudio{

class ISerializer{
public:
	virtual ~ISerializer(){};

	virtual void setName(const char *name) = 0;
	virtual const char *getName() const = 0;

	virtual bool addScene(std::shared_ptr<Scene> data) = 0;
	virtual std::vector<std::shared_ptr<Scene>> getScenes() const = 0;

	virtual void writeFile(const char *path) = 0;
	virtual void parseFile(const char *path) = 0;

	virtual std::shared_ptr<IMultiLevelStore> getStore() const = 0;
};

} // maudio

#endif // MAUDIO_ISERIALIZER




