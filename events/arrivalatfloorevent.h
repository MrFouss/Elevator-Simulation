#ifndef ARRIVALATFLOOREVENT_H
#define ARRIVALATFLOOREVENT_H

#include "events/ievent.h"
#include "data/elevator/abstractelevator.h"

class ArrivalAtFloorEvent : public IEvent
{
private:
    AbstractElevator* elevator;

public:
    ArrivalAtFloorEvent(float triggerTime, AbstractElevator* elevator) : IEvent(triggerTime), elevator(elevator) {}

    virtual void resolve();
};

#endif // ARRIVALATFLOOREVENT_H
