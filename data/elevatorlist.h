#ifndef ELEVATORLIST_H
#define ELEVATORLIST_H

#include <vector>
#include <list>

#include "configuration.h"
#include "data/enum.h"
#include "data/elevator.h"
#include "data/elevatorrequest.h"

class Elevator;

class ElevatorList
{
private:
    std::vector<Elevator*> elevatorList;
    std::list<ElevatorRequest*> elevatorRequestList;

public:
    ElevatorList(Configuration config);
    ~ElevatorList();

    bool isElevatorIdle();
    Elevator* getIdleElevator();

    void addRequest(ElevatorRequest* request);
    bool isRequestAvailable();
    std::list<ElevatorRequest*> getRequestListAtFloor(int floor);
    std::list<ElevatorRequest*> getRequestListAtFloor(int floor, Direction direction);

    int getNearestFloorWithRequest(int floor);
    int getNearestFloorWithRequest(int floor, Direction direction);
    bool areRequestAvailableInDirection(int floor, Direction direction);
};

#endif // ELEVATORLIST_H
