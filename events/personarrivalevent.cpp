#include <random>
#include <chrono>
#include <QDebug>

#include "events/personarrivalevent.h"
#include "events/callelevatorevent.h"

#include "singleton/simulationmanager.h"

void PersonArrivalEvent::resolve()
{
    SimulationManager::getInstance()->addEvent(new PersonArrivalEvent(triggerTime + 1.0));

    std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::poisson_distribution<int> poissonRng(Configuration::getInstance()->getMeanPoissonPersonArrival());
    int amountNewPersons = poissonRng(rng);
    for (int i = 0; i < amountNewPersons; i++)
    {
        Person* newPerson = new Person();
        newPerson->startWaitingElevator(triggerTime);
        SimulationManager::getInstance()->addEvent(new CallElevatorEvent(triggerTime, newPerson));

        qDebug().nospace().noquote() << "[" << QString().sprintf("%7.2f", triggerTime)
                                     << "] New P" << QString().sprintf("%03d", newPerson->getId());
    }
}
