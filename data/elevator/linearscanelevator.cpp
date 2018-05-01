#include "linearscanelevator.h"

void LinearScanElevator::invertDirection()
{
    if (direction == Direction::UP)
    {
        direction = Direction::DOWN;
    }
    else if (direction == Direction::DOWN)
    {
        direction = Direction::UP;
    }
}

bool LinearScanElevator::isFloorInRightDirection(int floor)
{
    return (direction == Direction::UP && floor >= floor)
            || (direction == Direction::DOWN && floor <= floor);
}

void LinearScanElevator::embark()
{
    std::list<ElevatorRequest*> requestList = elevatorList->getRequestListAtFloor(floor, direction);

    for (ElevatorRequest* request : requestList)
    {
        passengerList.push_back(request->getPerson());
        printEmbarkInfo(request);
        delete request;
    }
}

int LinearScanElevator::chooseFloor()
{
    Configuration* config = Configuration::getInstance();

    if (passengerList.empty())
    {
        if (elevatorList->isRequestAvailable())
        {
            if (elevatorList->areRequestAvailableInDirection(floor, direction, false))
            {
                if (elevatorList->areRequestAvailableInDirection(floor, direction, true))
                {
                    return elevatorList->getNearestFloorWithRequest(floor, direction, true);
                }
                else
                {
                    int targetFloor = elevatorList->getNearestFloorWithRequest(floor, direction, false);
                    invertDirection();
                    return targetFloor;
                }
            }
            else
            {
                invertDirection();
                embark();
                return chooseFloor();
            }
        }
        else
        {
            return idleFloor;
        }
    }
    else
    {
        return getNearestPassengerFloor();
    }
}
