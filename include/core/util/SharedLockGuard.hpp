/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#ifndef MAUDIO_SHAREDLOCKGUARD
#define MAUDIO_SHAREDLOCKGUARD

#include "core/util/RecursiveSharedMutex.hpp"

namespace maudio{

class lock_guard{
public:
	lock_guard(recursive_shared_mutex &mutex);
	~lock_guard();
	
private:
	lock_guard(const lock_guard &) = delete;
	lock_guard &operator=(const lock_guard &) = delete;
	
	recursive_shared_mutex &mMutex;
};

class shared_lock_guard{
public:
	shared_lock_guard(const recursive_shared_mutex &mutex);
	~shared_lock_guard();
	
private:
	shared_lock_guard(const shared_lock_guard &) = delete;
	shared_lock_guard &operator=(const shared_lock_guard &) = delete;
	
	recursive_shared_mutex &mMutex;
};

} // maudio

#endif // MAUDIO_SHAREDLOCKGUARD




