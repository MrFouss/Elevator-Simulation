#ifndef ABSTRACTELEVATOR_H
#define ABSTRACTELEVATOR_H

#include <list>

#include "data/elevatorlist.h"
#include "data/elevatorrequest.h"
#include "data/enum.h"
#include "data/person.h"

class ElevatorList;

class AbstractElevator
{
protected:
    static inline int idCount = 0;
    int id;

    // parent elevator list
    ElevatorList* elevatorList;

    int floor;
    int idleFloor;
    bool idle = true;

    std::list<Person*> passengerList;

    int getNearestPassengerFloor();

    void printEmbarkInfo(ElevatorRequest* request);

public:
    AbstractElevator(ElevatorList* elevatorList);

    int getId();

    int getCurrentFloor();
    void setCurrentFloor(int floor);

    bool isIdle();
    void setIdle(bool idle);

    std::list<Person*> disembark();
    virtual void embark() = 0;
    virtual int chooseFloor() = 0;
};

#endif // ABSTRACTELEVATOR_H
