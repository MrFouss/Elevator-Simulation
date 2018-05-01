#include "sstfelevator.h"

void SstfElevator::embark()
{
    std::list<ElevatorRequest*> requestList = elevatorList->getRequestListAtFloor(floor);

    for (ElevatorRequest* request : requestList)
    {
        passengerList.push_back(request->getPerson());
        printEmbarkInfo(request);
        delete request;
    }
}

int SstfElevator::chooseFloor()
{
    Configuration* config = Configuration::getInstance();

    if (passengerList.empty())
    {
        if (elevatorList->isRequestAvailable())
        {
            return elevatorList->getNearestFloorWithRequest(floor);
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
