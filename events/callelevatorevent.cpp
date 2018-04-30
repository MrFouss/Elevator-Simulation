#include <QDebug>

#include "events/callelevatorevent.h"
#include "events/arrivalatfloorevent.h"
#include "singleton/simulationmanager.h"

void CallElevatorEvent::resolve()
{
    SimulationManager* simulationManager = SimulationManager::getInstance();
    simulationManager->addElevatorRequest(
                new ElevatorRequest(person->getCurrentFloor(), person->getTargetFloor(), person));
    person->startWaitingElevator(triggerTime);

    qDebug().nospace().noquote() << "[" << QString().sprintf("%7.2f", triggerTime)
                                 << "] P" << QString().sprintf("%03d", person->getId()) << " called an elevator"
                                 << " (F" << person->getCurrentFloor() << " -> F" << person->getTargetFloor() << ")";

    if (simulationManager->isElevatorIdle())
    {
        Elevator* idleElevator = simulationManager->getIdleElevator();
        simulationManager->addEvent(new ArrivalAtFloorEvent(triggerTime, idleElevator));
        qDebug().nospace().noquote() << "[" << QString().sprintf("%7.2f", triggerTime)
                                     << "] E" << idleElevator->getId()
                                     << " called by P" << QString().sprintf("%03d", person->getId())
                                     << " (F" << person->getCurrentFloor() << " -> F" << person->getTargetFloor() << ")";
    }
}
