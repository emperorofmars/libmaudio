/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_TXTSERIALIZER
#define MAUDIO_TXTSERIALIZER

#include "core/serializer/ISerializer.hpp"
#include "core/store/MultiLevelStore.hpp"
#include <fstream>

namespace maudio{

class TXTSerializer : public ISerializer{
public:
	TXTSerializer(const char *name = "default_project");
	~TXTSerializer();

	virtual void setName(const char *name);
	virtual const char *getName() const;

	virtual bool addScene(std::shared_ptr<Scene> data);
	virtual std::vector<std::shared_ptr<Scene>> getScenes();

	virtual void writeFile(const char *path);
	virtual void parseFile(const char *path);

	virtual std::shared_ptr<IMultiLevelStore> getStore();
	
private:
	void writeHeader(std::ofstream &file);
	bool parseHeader(std::ifstream &file);
	
	std::string mName;
	std::shared_ptr<IMultiLevelStore> mStore;
	std::vector<std::shared_ptr<Scene>> mScenes;
};

} // maudio

#endif // MAUDIO_TXTSERIALIZER




