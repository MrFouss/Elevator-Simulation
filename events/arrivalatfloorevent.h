#ifndef ARRIVALATFLOOREVENT_H
#define ARRIVALATFLOOREVENT_H

#include "events/ievent.h"
#include "data/elevator/ielevator.h"

class ArrivalAtFloorEvent : public IEvent
{
private:
    Elevator* elevator;

public:
    ArrivalAtFloorEvent(float triggerTime, Elevator* elevator) : IEvent(triggerTime), elevator(elevator) {}

    virtual void resolve();
};

#endif // ARRIVALATFLOOREVENT_H
