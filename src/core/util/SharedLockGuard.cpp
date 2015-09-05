/*
 * Project Maudio
 * Copyright (C) 2015 Martin Schwarz
 * See LICENSE.txt for the full license
 */

#include "core/util/SharedLockGuard.hpp"

namespace maudio{

lock_guard::lock_guard(recursive_shared_mutex &mutex)
	: mMutex(mutex)
{
	mMutex.lock();
	return;
}

lock_guard::~lock_guard(){
	mMutex.unlock();
	return;
}


shared_lock_guard::shared_lock_guard(const recursive_shared_mutex &mutex)
	: mMutex((recursive_shared_mutex &)mutex)
{
	mMutex.lock_shared();
	return;
}

shared_lock_guard::~shared_lock_guard(){
	mMutex.unlock_shared();
	return;
}

} // maudio



