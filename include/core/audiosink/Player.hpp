/*
 * Class for playing Audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_PLAYER
#define MAUDIO_PLAYER

#include "core/audiosink/IAudioSink.hpp"
#include "core/util/AudioDevice.hpp"

namespace maudio{

class Player : public IAudioSink{
public:
	Player();
	Player(int device);
	Player(std::string &device);
	virtual ~Player();

	virtual void setSource(std::weak_ptr<IAudioSource> source);
	virtual std::shared_ptr<IAudioSource> getSource();

	void open();
	void open(int device);
	void open(std::string &device);
	void close();

	void play();
	void pause();
	void stop();
	void setPosition(unsigned long samples);
	unsigned long getPosition();
	void setPosition(float seconds);
	float getPosition();

    virtual AudioInfo getAudioInfo();
    virtual FileInfo getFileInfo();

private:
	//callbackfunc
	int deviceNameToNumber(std::string &name);

	AudioDevice *mDevice;
	std::weak_ptr<IAudioSource> mSource;
};

} // maudio

#endif // MAUDIO_PLAYER


