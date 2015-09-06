/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_TYPEMANAGER
#define MAUDIO_TYPEMANAGER

#include "maudio/action/IAction.hpp"
#include "maudio/util/sptr.hpp"

namespace maudio{

class TypeManager{
public:
	static sptr<IAction> create(const char *type, const char *name = NULL);
};

} // maudio

#endif // MAUDIO_TYPEMANAGER




