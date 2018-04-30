#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <list>

#include "configuration.h"
#include "data/elevatorlist.h"
#include "data/person.h"
#include "data/enum.h"

class ElevatorList;

class Elevator
{
private:
    static inline int idCount = 0;
    int id;

    ElevatorList* elevatorList;

    int currentFloor;
    bool idle = true;
    Direction direction = Direction::UP;
    std::list<Person*> passengerList;

    int getNearestPassengerFloor();
    void invertDirection();

public:
    Elevator(ElevatorList* elevatorList, Configuration config);

    int getId();

    int getCurrentFloor();
    void setCurrentFloor(int floor);

    bool isIdle();
    void setIdle(bool idle);

    bool isFloorInRightDirection(int floor);

    std::list<Person*> disembark();
    void embark();
    int chooseFloor();
};

#endif // ELEVATOR_H
