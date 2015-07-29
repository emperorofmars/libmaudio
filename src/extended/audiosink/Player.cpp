/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "extended/audiosink/Player.hpp"
#include "core/util/AudioException.hpp"
#include <iostream>

namespace maudio{

Player::Player(){
	open();
}

Player::Player(int device){
	open(device);
}

Player::Player(std::string &device){
	open(device);
}

Player::~Player(){
    close();
}

void Player::open(){
	mDevice = AudioDevice::open();
	return;
}

void Player::open(int device){
	mDevice = AudioDevice::open(device);
	return;
}

void Player::open(std::string &device){
	mDevice = AudioDevice::open(device);
	return;
}

void Player::close(){
    if(mDevice != NULL){
        stop();
        mDevice = NULL;
    }
	return;
}

std::vector<std::string> Player::listDevices(){
	std::vector<std::string> ret;
	if(mDevice) ret = mDevice->listDevices();
	return ret;
}

void Player::play(){
	if(!mDevice) throw InvalidAudioDeviceException();
	if(!checkInput(0)) throw MaudioException("invalid input");
	mQueue.reset(new AudioQueue(getInfoFromSlot(0)));
	feed();
	startFeed();
	mDevice->play(mQueue);
	return;
}

void Player::pause(){
	if(!mDevice) throw InvalidAudioDeviceException();
	stopFeed();
	mDevice->pause();
	return;
}

void Player::unpause(){
	if(!mDevice) throw InvalidAudioDeviceException();
	startFeed();
	mDevice->unpause();
	return;
}

void Player::stop(){
	if(!mDevice) throw InvalidAudioDeviceException();
	stopFeed();
	mDevice->stop();
	return;
}

void Player::setPosition(unsigned long samples){
	mPosition = samples;
	return;
}

unsigned long Player::getPosition(){
	return mPosition;
}

void Player::setPosition(float seconds){
	if(NumInputs() > 0){
		mPosition =  seconds * (float)getInfo().Samplerate;
	}
	return;
}

float Player::getPosition_sek(){
	if(NumInputs() > 0){
		return (float)mPosition / (float)getInfo().Samplerate;
	}
	return 0;
}

std::string Player::getStatus(){
	std::string status = "Player not opened";
	if(mDevice && mDevice->getStatus() == -1) status = "Device error";
	if(mDevice && mDevice->getStatus() == 0) status = "Device opened";
	if(mDevice && mDevice->getStatus() == 1) status = "Device playing";
	if(mDevice && mDevice->getStatus() == 2) status = "Device paused";
	return status;
}

bool Player::getOpened(){
	if(mDevice && mDevice->getStatus() >= 0) return true;
	return false;
}

bool Player::playing(){
	if(mDevice && mDevice->getStatus() >= 1) return true;
	return false;
}

void Player::readConfig(const Config &conf){
	unsigned int tmpQueueSize = conf.get<unsigned int>("PlayerQueueSize");
	if(tmpQueueSize >= 1024 && tmpQueueSize <= 1024 * 16)
		mQueueSize = tmpQueueSize;
    return;
}

void Player::feed(){
	if(!mQueue) return;
	if(NumInputs() == 0) return;
	if(mQueueSize <= mQueue->size()) return;

	for(unsigned int i = 0; i < mQueueSize - mQueue->size(); i++){
		AudioBuffer tmp = getFromSlot(mPosition, mQueueSize - mQueue->size(), 0);
		for(unsigned int j = 0; j < tmp.getInfo().Samples; j++){
			mQueue->push(tmp.get(j));
		}
		mPosition += tmp.getInfo().Samples;
	}
	return;
}

void Player::startFeed(){
	mFeederRun = true;
	mThread.reset(new std::thread(asyncFeed, this));
	return;
}

void Player::stopFeed(){
    if(mFeederRun){
        mFeederRun = false;
        if(mThread->joinable()) mThread->join();
        else mThread.reset();
    }
	return;
}

void Player::asyncFeed(Player *player){
	while(player && player->mFeederRun){
		player->feed();
		std::this_thread::sleep_for(std::chrono::milliseconds((player->mQueueSize / 2 * 44100) / 4000000));
	}
	return;
}

} // maudio







