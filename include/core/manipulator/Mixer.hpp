/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_MIXER
#define MAUDIO_MIXER

#include "core/manipulator/BaseManipulator.hpp"

namespace maudio{

class Mixer : public BaseManipulator{
public:
	virtual ~Mixer();

	virtual AudioBuffer get(unsigned long pos, unsigned int length) noexcept;
	virtual AudioInfo getInfo() noexcept;
	virtual int MaxInputs() const;
	virtual bool checkIfCompatible(std::shared_ptr<Node> node, int slot = -1);
};

} // maudio

#endif // MAUDIO_MIXER


