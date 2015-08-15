/*
* Project Maudio
* Copyright (C) 2015 Martin Schwarz
* See LICENSE.txt for the full license
*/

#include "maudio.hpp"

using namespace maudio;

class TestPlugin : public BaseAction{
public:
	TestPlugin(){};
	virtual ~TestPlugin(){};
	
	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept{
		return NULL;
	};
	virtual IAudioInfo *getInfo() noexcept{
		IAudioInfo *ret = new AudioInfo();
		ret->setSamplerate(666);
		return ret;
	};

	virtual int MaxInputs() const{
		return 0;
	};
	virtual bool HasOutputs() const{
		return false;
	};

	virtual void readConfig(const IKeyValueStore &conf){
		return;
	};
/*
	virtual IKeyValueStore *serialize() const = 0;
	virtual void deserialize(const IKeyValueStore *data) = 0;
*/
};

extern "C" void* create(){
	return new TestPlugin();
}

extern "C" void destroy(void *data){
	delete (TestPlugin *)data;
}

extern "C" const char *getName(){
	static const char *ret = "TestPlugin";
	return ret;
}






