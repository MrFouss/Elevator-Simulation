#include <iostream>

#include "simulationmanager.h"
#include "events/personarrivalevent.h"

using namespace std;

int main()
{
    cout << "###########################" << endl;
    cout << "# STARTING THE SIMULATION #" << endl;
    cout << "###########################" << endl << endl;

    SimulationManager* simulationManager = SimulationManager::getInstance();
    simulationManager->printConfigurationSettings();

    // initiate a first event to start the simulation
    simulationManager->addEvent(new PersonArrivalEvent(0.0));

    while (simulationManager->isNextEventSolvable())
    {
        simulationManager->resolveNextEvent();
    }

    // destroy remaining objects
    SimulationManager::deleteInstance();

    return 0;
}
