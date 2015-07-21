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
#include <thread>

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
	void unpause();
	void stop();

	void setPosition(unsigned long samples);
	unsigned long getPosition();
	void setPosition(float seconds);
	float getPosition_sek();

	std::string getStatus();
	bool getOpened();
	bool playing();

private:
	void feed();
	void startFeed();
	void stopFeed();
	static void asyncFeed(Player *player);

	AudioDevice *mDevice;
	std::shared_ptr<AudioQueue> mQueue;
	std::shared_ptr<std::thread> mThread;
	bool mFeederRun = false;
	unsigned long mPosition = 0;

	unsigned int mQueueSize = 44100;
};

} // maudio

#endif // MAUDIO_PLAYER


