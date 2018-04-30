#ifndef CALLELEVATOREVENT_H
#define CALLELEVATOREVENT_H

#include "ievent.h"
#include "data/person.h"

class CallElevatorEvent : public IEvent
{
private:
    Person* person;

public:
    CallElevatorEvent(float triggerTime, Person* person) : IEvent(triggerTime), person(person) {}

    virtual void resolve();
};

#endif // CALLELEVATOREVENT_H
