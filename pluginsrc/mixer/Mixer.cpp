/*
* Project Maudio
* Copyright (C) 2015 Martin Schwarz
* See LICENSE.txt for the full license
*/

#include "maudio.hpp"

using namespace maudio;

class Mixer : public BaseAction{
public:
	Mixer(){};
	virtual ~Mixer(){};
	
	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept{
		simple_ptr<IAudioInfo> info(getInfo());
		AudioBuffer *ret = new AudioBuffer(info->getChannels(), length, pos, info->getSamplerate());
		if(NumInputs() > 0){
			for(int i = 0; i < NumInputs(); i++){
				auto tmp = getFromSlot(i, pos, length);
				for(unsigned int j = 0; j < length; j++){
					simple_ptr<ISample> smp1(ret->get(j));
					action_ptr<ISample> smp2(tmp->get(j), mInputs[i]);
					*smp1 += *smp2;
					ret->set(*smp1, j);
				}
			}
			for(unsigned int j = 0; j < length; j++){
				simple_ptr<ISample> smp(ret->get(j));
				*smp /= (float)NumInputs();
				ret->set(*smp, j);
			}
		}
		return ret;
	};
	
	virtual IAudioInfo *getInfo() noexcept{
		if(NumInputs() == 0) return NULL;
		auto info = getInfoFromSlot(0);
		if(!info) return NULL;
		AudioInfo *ret = new AudioInfo();
		*ret = *info;
		return ret;
	};

	virtual int MaxInputs() const{
		return -1;
	};
	virtual bool HasOutputs() const{
		return true;
	};

	virtual void readConfig(const IKeyValueStore &conf){
		return;
	};

	virtual void serialize(IMultiLevelStore *data) const{
		return;
	};
	
	virtual void deserialize(const IMultiLevelStore *data){
		return;
	};
	
};

extern "C" void* create(){
	return new Mixer();
}

extern "C" void destroy(void *data){
	delete (Mixer *)data;
}

extern "C" const char *getName(){
	static const char *ret = "Mixer";
	return ret;
}






