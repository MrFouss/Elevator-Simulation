#ifndef ELEVATORLIST_H
#define ELEVATORLIST_H

#include <vector>
#include <list>

#include "singleton/configuration.h"
#include "data/enum.h"
#include "data/elevator/abstractelevator.h"
#include "data/elevatorrequest.h"

class AbstractElevator;

class ElevatorList
{
private:
    std::vector<AbstractElevator*> elevatorList;
    std::list<ElevatorRequest*> elevatorRequestList;

public:
    ElevatorList();
    ~ElevatorList();

    bool isElevatorIdle();
    AbstractElevator* getIdleElevator();

    void addRequest(ElevatorRequest* request);
    bool isRequestAvailable();
    std::list<ElevatorRequest*> getRequestListAtFloor(int floor);
    std::list<ElevatorRequest*> getRequestListAtFloor(int floor, Direction direction);

    int getNearestFloorWithRequest(int floor);
    int getNearestFloorWithRequest(int floor, Direction direction, bool isRequestSameDirection);
    bool areRequestAvailableInDirection(int floor, Direction direction, bool isRequestSameDirection);
};

#endif // ELEVATORLIST_H
