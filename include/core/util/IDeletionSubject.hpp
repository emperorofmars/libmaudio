/*
 * Interface for registering connected objects
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#ifndef MAUDIO_IDELETIONSUBJECT
#define MAUDIO_IDELETIONSUBJECT

namespace maudio{

class IDeletionSubject{
public:
	virtual ~IDeletionSubject(){};

    virtual void checkIn(IDeletionObserver *obj) = 0;
    virtual void checkOut(IDeletionObserver *obj) = 0;
};

} // maudio

#endif // MAUDIO_IDELETIONSUBJECT


