/*
 * Copyright (C) 2015 Martin Schwarz
 */

#include "core/audiosink/Player.hpp"
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
	return;
}

void Player::open(std::string &device){
	return;
}

void Player::close(){
	return;
}

std::vector<std::string> Player::listDevices(){
	std::vector<std::string> ret;
	if(mDevice) ret = mDevice->listDevices();
	return ret;
}

void Player::play(){
	if(!mDevice) throw InvalidAudioDeviceException();
	AudioInfo tmp;
	tmp.Channels = 1;
	tmp.Samplerate = 44100;
	mQueue.reset(new AudioQueue(tmp));
	startFeed();
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
	//if(mInputs.size() > 0 && mInputs[0] && mInputs[0]->valid()){
	//	mPosition =  seconds * (float)mInputs[0]->getInput()->getAudioInfo().Samplerate;
	//}
	return;
}

float Player::getPosition_sek(){
	//if(mInputs.size() > 0 && mInputs[0] && mInputs[0]->valid()){
	//	return (float)mPosition / (float)mInputs[0]->getInput()->getAudioInfo().Samplerate;
	//}
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

AudioInfo Player::getAudioInfo(){
	//if(mInputs.size() > 0 && mInputs[0] && mInputs[0]->valid()) return mInputs[0]->getInput()->getAudioInfo();
	return AudioInfo();
}

void Player::feed(){
	if(!mQueue) return;
	//if(mInputs.size() == 0 || !mInputs[0] || !mInputs[0]->valid()) return;

	//mQueue->lock();
	for(unsigned int i = 0; i < mQueueSize - mQueue->size(); i++){
		try{
			//mQueue->push(mInputs[0]->getInput()->get(mPosition));
			mPosition++;
		}
		catch(std::exception &e){
			std::cerr << "feed error: " << e.what() << std::endl;
		}
		catch(...){
			std::cerr << "feed error" << std::endl;
		}
	}

	//mQueue->unlock();
	return;
}

void Player::startFeed(){
	mFeederRun = true;
	mThread.reset(new std::thread(asyncFeed, this));
	return;
}

void Player::stopFeed(){
	mFeederRun = false;
	if(mThread->joinable()) mThread->join();
	mThread.reset();
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







