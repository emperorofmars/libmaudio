/*
 * Interface for releasing audio
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_TERMINALPRINTER
#define MAUDIO_TERMINALPRINTER

#include "core/audiosink/IAudioSink.hpp"
#include <memory>

namespace maudio{

class TerminalPrinter : public IAudioSink{
public:
	TerminalPrinter();
	virtual ~TerminalPrinter();

	virtual void setSource(std::shared_ptr<IAudioSource> source);
	virtual std::shared_ptr<IAudioSource> getSource();
	void print(unsigned long pos);

private:
	std::weak_ptr<IAudioSource> mSource;
};

} // maudio

#endif // MAUDIO_TERMINALPRINTER


