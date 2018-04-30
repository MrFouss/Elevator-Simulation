#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <vector>

#include "events/eventlist.h"
#include "events/ievent.h"
#include "data/person.h"
#include "data/elevatorlist.h"

class SimulationManager
{
private:
    // SimulationManager instance
    static inline SimulationManager* instance = nullptr;

    // attributes related to the event list
    EventList eventList;
    float currentTime = 0.0;

    // data attributes
    std::vector<float> waitTimeList;
    ElevatorList* elevatorList;

    // constructor and destructor
    SimulationManager();
    ~SimulationManager();

public:
    static SimulationManager* getInstance();
    static void deleteInstance();

    float getAverageWaitTime();

    // methods related to the event list
    void addEvent(IEvent* event);
    bool isNextEventSolvable();
    void resolveNextEvent();

    float getCurrentTime();

    bool isElevatorIdle();
    Elevator* getIdleElevator();

    void addElevatorRequest(ElevatorRequest* request);

    void exitPerson(Person* person);
};

#endif // SIMULATIONMANAGER_H
