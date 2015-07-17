/*
 * Interface for notifying of deletion of connected objects
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_IDELETIONOBSERVER
#define MAUDIO_IDELETIONOBSERVER

namespace maudio{

class IDeletionObserver{
public:
	virtual ~IDeletionObserver(){};

	virtual void handleDeletion(void *obj) = 0;
};

} // maudio

#endif // MAUDIO_IDELETIONOBSERVER


