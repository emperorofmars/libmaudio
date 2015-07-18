/*
 * Prints values to cout
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_TERMINALPRINTER
#define MAUDIO_TERMINALPRINTER

#include "core/audiosink/BaseAudioSink.hpp"

namespace maudio{

class TerminalPrinter : public BaseAudioSink{
public:
	TerminalPrinter();
	virtual ~TerminalPrinter();

	void print(unsigned long pos) const;

    virtual AudioInfo getAudioInfo();
    virtual FileInfo getFileInfo();

protected:
	AudioInfo mAudioInfo;
	FileInfo mFileInfo;
};

} // maudio

#endif // MAUDIO_TERMINALPRINTER


