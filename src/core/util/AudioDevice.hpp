/*
 * Class for managing audiodevices
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_AUDIODEVICE
#define MAUDIO_AUDIODEVICE

#include <string>
#include <vector>

namespace maudio{

class AudioDevice{
public:
	AudioDevice* open();
	AudioDevice* open(int device);
	AudioDevice* open(std::string &device);

	std::vector<std::string> listDevices();

	void refresh();

private:
	AudioDevice(const AudioDevice &) = delete;
	void operator=(const AudioDevice &) = delete;

	AudioDevice();
	virtual ~AudioDevice();

	static std::vector<AudioDevice*> mDevices;
};

} // maudio

#endif // MAUDIO_AUDIODEVICE


