/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PROJECT
#define MAUDIO_PROJECT

#include "maudio/scene/Scene.hpp"
#include <memory>
#include <string>
#include <vector>
#include <mutex>

namespace maudio{

class Project{
public:
	Project(const char *name = "default_project");
	~Project();

	void setName(const char *name);
	const char *getName() const;
	
	void addScene(std::shared_ptr<Scene> scene);
	void removeScene(unsigned int num);
	void removeScene(const char *name);
	std::shared_ptr<Scene> getScene(unsigned int num) const;
	std::shared_ptr<Scene> getScene(const char *name) const;
	unsigned int getNumScenes() const;
	
	void save() const;
	void load(const char *file);
	
	void setSaveFile(const char *file);
	const char *getSaveFile() const;
	void setPreservePrevious(bool preserve);
	bool getPreservePrevious() const;
	
	void readConfig(const IKeyValueStore *conf);
	
private:
	int getSceneNum(const char *name) const;
	
	std::string mName;
	std::string mSaveFile;
	bool mPreservePrevious = true;
	std::vector<std::shared_ptr<Scene>> mScenes;
	mutable std::recursive_mutex mMutex;
};

} // maudio

#endif // MAUDIO_PROJECT




