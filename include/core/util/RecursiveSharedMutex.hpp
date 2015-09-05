/*
* Project Maudio
* Copyright (C) 2015 Martin Schwarz
* See LICENSE.txt for the full license
*/

#ifndef MAUDIO_RECURSIVESHAREDMUTEX
#define MAUDIO_RECURSIVESHAREDMUTEX

#include <mutex>

namespace maudio{

class recursive_shared_mutex{
public:
	recursive_shared_mutex();
	~recursive_shared_mutex();
	
	void lock();
	bool try_lock();
	void unlock();
	
	void lock_shared();
	bool try_lock_shared();
	void unlock_shared();
	
private:
	recursive_shared_mutex(const recursive_shared_mutex &) = delete;
	recursive_shared_mutex &operator=(const recursive_shared_mutex &) = delete;
	
	unsigned int mLockLevel = 0;
	std::recursive_mutex mMutex;
	std::mutex mSharedMutex;
};

} // maudio

#endif // MAUDIO_RECURSIVESHAREDMUTEX




