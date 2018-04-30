#ifndef ARRIVALATFLOOREVENT_H
#define ARRIVALATFLOOREVENT_H

#include "ievent.h"
#include "data/elevator.h"

class ArrivalAtFloorEvent : public IEvent
{
private:
    Elevator* elevator;

public:
    ArrivalAtFloorEvent(float triggerTime, Elevator* elevator) : IEvent(triggerTime), elevator(elevator) {}

    virtual void resolve();
};

#endif // ARRIVALATFLOOREVENT_H
