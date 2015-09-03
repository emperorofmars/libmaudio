/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_TYPEMANAGER
#define MAUDIO_TYPEMANAGER

#include "core/action/IAction.hpp"
#include "core/util/sptr.hpp"

namespace maudio{

class TypeManager{
public:
	static sptr<IAction> create(const char *type);
};

} // maudio

#endif // MAUDIO_TYPEMANAGER




