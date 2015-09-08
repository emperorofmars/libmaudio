/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_ICONTROL
#define MAUDIO_ICONTROL

#include "maudio/util/BaseObservable.hpp"
#include <cstddef>

namespace maudio{

class IControl : public BaseObservable{
public:
	virtual ~IControl(){};

	virtual unsigned int getNumFunctions() = 0;
	virtual const char *getFunctionName(unsigned int num) = 0;
	virtual const char *getFunctionParam(unsigned int num) = 0;
	virtual const char *callFunction(unsigned int num, const char *param = NULL) = 0;
	virtual const char *callFunction(const char *name, const char *param = NULL) = 0;
	virtual void stop() = 0;
};

} // maudio

#endif // MAUDIO_ICONTROL




