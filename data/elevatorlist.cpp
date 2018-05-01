#include "elevatorlist.h"

#include <cmath>
#include <limits>
#include <QDebug>

#include "data/elevator/sstfelevator.h"
#include "data/elevator/linearscanelevator.h"

#include "singleton/simulationmanager.h"

ElevatorList::ElevatorList()
{
    Configuration* config = Configuration::getInstance();
    for (int i = 0; i < config->getAmountElevators(); ++i)
    {
        AbstractElevator* newElevator;

        switch (config->getBusyScheduling())
        {
        case BusyScheduling::SHORTEST_SEEK_TIME_FIRST:
            newElevator = new SstfElevator(this);
            break;

        case BusyScheduling::LINEAR_SCAN:
            newElevator = new LinearScanElevator(this);
            break;

        default:
            qFatal("Unknown busy scheduling!");
            break;
        }

        elevatorList.push_back(newElevator);
    }
}

ElevatorList::~ElevatorList()
{
    for (AbstractElevator* elevator : elevatorList)
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
    for (AbstractElevator* elevator : elevatorList)
    {
        if (elevator->isIdle())
        {
            return true;
        }
    }

    return false;
}

AbstractElevator* ElevatorList::getIdleElevator()
{
    for (AbstractElevator* elevator : elevatorList)
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
