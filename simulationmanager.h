#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include<map>
#include <vector>

#include "events/eventlist.h"
#include "events/ievent.h"
#include "data/person.h"

class SimulationManager
{
private:
    // SimulationManager instance
    static inline SimulationManager* instance = nullptr;

    // configuration attributes
    static constexpr inline char CONFIG_FILE_PATH[] = ":/configuration/default";
    int amountFloors = 7;
    int amountElevators = 2;
    float endOfSimulationTime = 43200.0;
    float meanPoissonPersonArrival = 0.5;

    // attributes related to the event list
    EventList eventList;

    // data attributes
    std::vector<std::vector<Person*>> waitingForElevatorPeopleList;

    // constructor and destructor
    SimulationManager();
    ~SimulationManager();

public:
    static SimulationManager* getInstance();
    static void deleteInstance();

    // configuration methods
    void printConfigurationSettings();
    int getAmountFloors();
    int getAmountElevators();
    float getMeanPoissonPersonArrival();

    // methods related to the event list
    void addEvent(IEvent* event);
    bool isNextEventSolvable();
    void resolveNextEvent();

    void addPersonWaitingForElevator(int floor, Person* person);
};

#endif // SIMULATIONMANAGER_H
