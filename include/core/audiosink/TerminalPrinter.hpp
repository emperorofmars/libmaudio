/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_TERMINALPRINTER
#define MAUDIO_TERMINALPRINTER

#include "core/audiosink/BaseAudioSink.hpp"

namespace maudio{

class TerminalPrinter : public BaseAudioSink{
public:
	TerminalPrinter();
	virtual ~TerminalPrinter();

	virtual AudioInfo getInfo() noexcept;
	virtual void readConfig(const Config &conf);

	void print(unsigned long pos);
};

} // maudio

#endif // MAUDIO_TERMINALPRINTER


