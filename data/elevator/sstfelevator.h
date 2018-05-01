#ifndef SSTFELEVATOR_H
#define SSTFELEVATOR_H

#include "data/elevator/abstractelevator.h"

class SstfElevator : public AbstractElevator
{
public:
    SstfElevator(ElevatorList* elevatorList) : AbstractElevator(elevatorList) {}

    virtual void embark();
    virtual int chooseFloor();
};

#endif // SSTFELEVATOR_H
