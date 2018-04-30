#include <random>
#include <chrono>
#include <cmath>
#include <QDebug>

#include "arrivalatfloorevent.h"
#include "simulationmanager.h"
#include "callelevatorevent.h"

void ArrivalAtFloorEvent::resolve()
{
    for (Person* person : elevator->disembark())
    {
        person->endWaitingElevator(triggerTime);

        if (person->getTargetFloor() == 1)
        {
            qDebug().nospace().noquote() << "[" << QString().sprintf("%7.2f", triggerTime)
                                         << "] P" << QString().sprintf("%03d", person->getId())
                                         << " exited (wait time: " << person->getTotalWaitTime() << ")";

            SimulationManager::getInstance()->exitPerson(person);
        }
        else
        {
            person->setCurrentFloor(person->getTargetFloor());
            person->setTargetFloor(1);

            std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
            std::exponential_distribution<float> exponentialRng(
                        1.0 / SimulationManager::getInstance()->getConfig().getMeanExponentialWorkTime());

            // get the work time in minutes
            float workTime = exponentialRng(rng);

            SimulationManager::getInstance()->addEvent(new CallElevatorEvent(triggerTime + workTime, person));

            qDebug().nospace().noquote() << "[" << QString().sprintf("%7.2f", triggerTime)
                                         << "] P" << QString().sprintf("%03d", person->getId())
                                         << " arrived at F" << person->getCurrentFloor()
                                         << " with E" << elevator->getId()
                                         << " (work ends in " << workTime << ")";
        }
    }

    elevator->embark();

    int newFloor = elevator->chooseFloor();

    elevator->setIdle(elevator->getCurrentFloor() == newFloor);

    if (!elevator->isIdle())
    {
        qDebug().nospace().noquote() << "[" << QString().sprintf("%7.2f", triggerTime)
                                     << "] Time to wait for E" << elevator->getId()
                                     << " to reach F" << elevator->getCurrentFloor()
                                     << " -> F" << newFloor << ": "
                                     << QString().sprintf("%.2f", (1.0/6.0) * std::abs(elevator->getCurrentFloor() - newFloor))
                                     << " (at " << QString().sprintf("%.2f", triggerTime + (1.0/6.0) * std::abs(elevator->getCurrentFloor() - newFloor))
                                     << ")";
        SimulationManager::getInstance()->addEvent(
                    new ArrivalAtFloorEvent(triggerTime + (1.0/6.0) * std::abs(elevator->getCurrentFloor() - newFloor), elevator));
        elevator->setCurrentFloor(newFloor);
    }
}
