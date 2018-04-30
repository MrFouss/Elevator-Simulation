#include <cmath>
#include <limits>
#include <QDebug>

#include "elevatorlist.h"
#include "simulationmanager.h"

ElevatorList::ElevatorList(Configuration config)
{
    for (int i = 0; i < config.getAmountElevators(); ++i)
    {
        elevatorList.push_back(new Elevator(this, config));
    }
}

ElevatorList::~ElevatorList()
{
    for (Elevator* elevator : elevatorList)
    {
        delete elevator;
    }

    for (ElevatorRequest* elevatorRequest : elevatorRequestList)
    {
        delete elevatorRequest;
    }
}

bool ElevatorList::isElevatorIdle()
{
    for (Elevator* elevator : elevatorList)
    {
        if (elevator->isIdle())
        {
            return true;
        }
    }

    return false;
}

Elevator* ElevatorList::getIdleElevator()
{
    for (Elevator* elevator : elevatorList)
    {
        if (elevator->isIdle())
        {
            return elevator;
        }
    }

    return nullptr;
}

void ElevatorList::addRequest(ElevatorRequest* request)
{
    elevatorRequestList.push_back(request);
}

bool ElevatorList::isRequestAvailable()
{
    return !elevatorRequestList.empty();
}

std::list<ElevatorRequest*> ElevatorList::getRequestListAtFloor(int floor)
{
    std::list<ElevatorRequest*> newRequestList;

    for (ElevatorRequest* request : elevatorRequestList)
    {
        if (request->getStartFloor() == floor)
        {
            newRequestList.push_back(request);
        }
    }

    for (ElevatorRequest* request : newRequestList)
    {
        elevatorRequestList.remove(request);
    }

    return newRequestList;
}

std::list<ElevatorRequest*> ElevatorList::getRequestListAtFloor(int floor, Direction direction)
{
    std::list<ElevatorRequest*> newRequestList;

    for (ElevatorRequest* request : elevatorRequestList)
    {
        if (request->getStartFloor() == floor
                && ((direction == Direction::UP && request->getEndFloor() > request->getStartFloor())
                    || (direction == Direction::DOWN && request->getEndFloor() < request->getStartFloor())))
        {
            newRequestList.push_back(request);
        }
    }

    for (ElevatorRequest* request : newRequestList)
    {
        elevatorRequestList.remove(request);
    }

    return newRequestList;
}

int ElevatorList::getNearestFloorWithRequest(int floor)
{
    if (elevatorRequestList.empty())
    {
        return -1;
    }

    int nearestFloor = std::numeric_limits<int>::max();

    for (ElevatorRequest* request : elevatorRequestList)
    {
        if (std::abs(request->getStartFloor() - floor) < std::abs(nearestFloor - floor))
        {
            nearestFloor = request->getStartFloor();
        }
    }

    return nearestFloor;
}

int ElevatorList::getNearestFloorWithRequest(int floor, Direction direction, bool isRequestSameDirection)
{
    if (!areRequestAvailableInDirection(floor, direction, isRequestSameDirection))
    {
        return -1;
    }

    int nearestFloor = std::numeric_limits<int>::max();

    for (ElevatorRequest* request : elevatorRequestList)
    {
        if (std::abs(request->getStartFloor() - floor) < std::abs(nearestFloor - floor)
                && ((direction == Direction::UP && request->getStartFloor() >= floor)
                    || (direction == Direction::DOWN && request->getStartFloor() <= floor)))
        {
            if (!isRequestSameDirection || direction == request->getDirection())
            {
                nearestFloor = request->getStartFloor();
            }
        }
    }

    return nearestFloor;
}

bool ElevatorList::areRequestAvailableInDirection(int floor, Direction direction, bool isRequestSameDirection)
{
    for (ElevatorRequest* request : elevatorRequestList)
    {
        if ((direction == Direction::UP
             && request->getStartFloor() >= floor)
                || (direction == Direction::DOWN
                    && request->getStartFloor() <= floor))
        {
            if (!isRequestSameDirection || direction == request->getDirection())
            {
                return true;
            }
        }
    }

    return false;
}
