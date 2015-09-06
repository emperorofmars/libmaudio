/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_TERMINALPRINTER
#define MAUDIO_TERMINALPRINTER

#include "core/action/BaseAction.hpp"
#include <memory>

namespace maudio{

class TerminalPrinter : public BaseAction{
public:
	TerminalPrinter();
	virtual ~TerminalPrinter();

	virtual IAudioBuffer *get(unsigned long pos, unsigned int length) noexcept;
	virtual IAudioInfo *getInfo() noexcept;

	virtual int MaxInputs() const;
	virtual bool HasOutputs() const;

	virtual void readConfig(const IKeyValueStore *conf);

	virtual IControl *getControl();

	virtual bool checkCompatible(IAudioInfo *info);

	virtual void serialize(IMultiLevelStore *data) const;
	virtual void deserialize(const IMultiLevelStore *data);

	void print(unsigned long pos);

private:
	class Control : public IControl{
	public:
		Control(TerminalPrinter *data);
		virtual ~Control();

		virtual unsigned int getNumFunctions();
		virtual const char *getFunctionName(unsigned int num);
		virtual const char *getFunctionParam(unsigned int num);
		virtual unsigned int callFunction(unsigned int num, const char *param = NULL);
		virtual unsigned int callFunction(const char *name, const char *param = NULL);
		virtual void stop();

	private:
		TerminalPrinter *mData = NULL;
	};
	std::shared_ptr<Control> mControl = std::make_shared<Control>(this);
};

} // maudio

#endif // MAUDIO_TERMINALPRINTER


