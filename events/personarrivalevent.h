#ifndef PERSONARRIVALEVENT_H
#define PERSONARRIVALEVENT_H

#include "ievent.h"

class   PersonArrivalEvent : public IEvent
{
public:
    PersonArrivalEvent(float triggerTime) : IEvent(triggerTime) {}

    virtual void resolve();
};

#endif // PERSONARRIVALEVENT_H
