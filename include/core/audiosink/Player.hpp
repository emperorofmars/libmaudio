/*
 * Class for playing Audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_PLAYER
#define MAUDIO_PLAYER

#include "core/audiosink/BaseAudioSink.hpp"
#include "core/util/AudioDevice.hpp"
#include "core/audiodata/AudioQueue.hpp"

namespace maudio{

class Player : public BaseAudioSink{
public:
	Player();
	Player(int device);
	Player(std::string &device);
	virtual ~Player();

	void open();
	void open(int device);
	void open(std::string &device);
	void close();

	std::vector<std::string> listDevices();

	void play();
	void pause();
	void stop();
	void setPosition(unsigned long samples);
	unsigned long getPosition();
	void setPosition(float seconds);
	float getPosition();

	std::string getStatus();
	bool getOpened();
	bool playing();

    virtual AudioInfo getAudioInfo();
    virtual FileInfo getFileInfo();

private:
	AudioDevice *mDevice;
	std::shared_ptr<AudioQueue> mQueue;
};

} // maudio

#endif // MAUDIO_PLAYER


