#include<random>
#include<iostream>
#include<map>

#include "personarrivalevent.h"
#include "../simulationmanager.h"

void PersonArrivalEvent::resolve()
{
    static std::default_random_engine rng;

    SimulationManager::getInstance()->addEvent(new PersonArrivalEvent(triggerTime + 60.0));

    std::poisson_distribution<int> poisson(SimulationManager::getInstance()->getMeanPoissonPersonArrival());
    int amountNewPersons = poisson(rng);
    for (int i = 0; i < amountNewPersons; i++)
    {
        Person* newPerson = new Person();
        newPerson->startWaitingElevator(triggerTime);
        SimulationManager::getInstance()->addPersonWaitingForElevator(1, newPerson);
    }

    std::cout << "Amount of new persons at time " << triggerTime << ": " << amountNewPersons << std::endl;
}
