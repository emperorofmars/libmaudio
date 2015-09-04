/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_PROJECT
#define MAUDIO_PROJECT

#include "core/scene/Scene.hpp"
#include <memory>
#include <string>
#include <vector>

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
	void getScene(unsigned int num);
	void getScene(const char *name);
	
	void save();
	void load(const char *file);
	
	void setSaveFile(const char *file);
	void setSaveHistory(unsigned int len = 2);
	const char *getSaveFile();
	unsigned int getSaveHistory();
	
	void readConfig(const IKeyValueStore *conf);
	
private:
	std::string mName;
	std::string mSaveFile;
	unsigned int mSaveHistory = 2;
	std::vector<std::shared_ptr<Scene>> mScenes;
};

} // maudio

#endif // MAUDIO_PROJECT




