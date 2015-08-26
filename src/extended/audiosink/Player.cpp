/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "extended/audiosink/Player.hpp"
#include "core/util/simple_ptr.hpp"
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
	if(mInputs.size() < 1 || !mInputs[0]) throw MaudioException("no or invalid input");

	mQueue.reset(new AudioQueue(*getInfoFromSlot(0)));
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
		simple_ptr<IAudioInfo> info(getInfo());
		mPosition =  seconds * (float)info->getSamplerate();
	}
	return;
}

float Player::getPosition_sek(){
	if(NumInputs() > 0){
		simple_ptr<IAudioInfo> info(getInfo());
		return (float)mPosition / (float)info->getSamplerate();
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

IAudioBuffer *Player::get(unsigned long pos, unsigned int length) noexcept{
	return NULL;
}

IAudioInfo *Player::getInfo() noexcept{
	return NULL;
}

int Player::MaxInputs() const{
	return 1;
}

bool Player::HasOutputs() const{
	return false;
}

void Player::readConfig(const IKeyValueStore &conf){
	try{
	//unsigned int tmpQueueSize = conf.get<unsigned int>("PlayerQueueSize");
	//if(tmpQueueSize >= 1024 && tmpQueueSize <= 1024 * 16)
	//	mQueueSize = tmpQueueSize;
	}
	catch(std::exception &e){
	}
    return;
}

IControl *Player::getControl(){
	return mControl.get();
}

bool Player::checkCompatible(IAudioInfo *info){
	return false;
}

void Player::serialize(IMultiLevelStore *data) const{
	return;
}

void Player::deserialize(const IMultiLevelStore *data){
	return;
}

void Player::feed(){
	if(!mQueue) return;
	if(NumInputs() == 0) return;
	if(mQueueSize <= mQueue->size()) return;

	for(unsigned int i = 0; i < mQueueSize - mQueue->size(); i++){
		auto tmp = getFromSlot(0, mPosition, mQueueSize - mQueue->size());
		for(unsigned int j = 0; j < tmp->getInfo()->getSamples(); j++){
			ISample *tmpSample = tmp->get(j);
			mQueue->push(*tmpSample);
			delete tmpSample;
		}
		mPosition += tmp->getInfo()->getSamples();
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


Player::Control::Control(Player *data){
	mData = data;
}

Player::Control::~Control(){
}

unsigned int Player::Control::getNumFunctions(){
	return 2;
}

const char *Player::Control::getFunctionName(unsigned int num){
	if(num == 0) return "play";
	if(num == 1) return "stop";
	return NULL;
}

const char *Player::Control::getFunctionParam(unsigned int num){
	if(num == 0) return "void";
	if(num == 1) return "void";
	return NULL;
}

unsigned int Player::Control::callFunction(unsigned int num, const char *param){
	if(num == 0){
		mData->play();
		return 0;
	}
	if(num == 1){
		mData->stop();
		return 0;
	}
	return -1;
}

unsigned int Player::Control::callFunction(const char *name, const char *param){
	if(std::string("play") == std::string(name)){
		mData->play();
		return 0;
	}
	if(std::string("stop") == std::string(name)){
		mData->stop();
		return 0;
	}
	return -1;
}

void Player::Control::stop(){
	mData->stop();
	return;
}

} // maudio







