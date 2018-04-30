#include <cmath>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QDebug>

#include "simulationmanager.h"

SimulationManager::SimulationManager()
{
    qDebug().nospace().noquote() << "Initialization of the simulation manager...";

    configuration.setup(":/configuration/default");
    configuration.printConfigurationSettings();

    elevatorList = new ElevatorList(configuration);

    qDebug().nospace().noquote() << "End of initialization of the simulation manager";
}

SimulationManager::~SimulationManager()
{
    delete elevatorList;
}

SimulationManager* SimulationManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SimulationManager();
    }

    return instance;
}

void SimulationManager::deleteInstance()
{
    idCount++;
    delete instance;
    instance = nullptr;
}

Configuration SimulationManager::getConfig() const
{
    return configuration;
}

float SimulationManager::getAverageWaitTime()
{
    float average = 0.0;

    for (float value : waitTimeList)
    {
        average += (value / waitTimeList.size());
    }

    return average;
}

void SimulationManager::addEvent(IEvent* event)
{
    eventList.add(event);
}

bool SimulationManager::isNextEventSolvable()
{
    return !eventList.isEmpty() && eventList.getNextEventTime() <= configuration.getEndOfSimulationTime();
}

void SimulationManager::resolveNextEvent()
{
    IEvent* event = eventList.pop();
    currentTime = event->getTriggerTime();
    event->resolve();
    delete event;
}

float SimulationManager::getCurrentTime()
{
    return currentTime;
}

bool SimulationManager::isElevatorIdle()
{
    return elevatorList->isElevatorIdle();
}

Elevator* SimulationManager::getIdleElevator()
{
    return elevatorList->getIdleElevator();
}

void SimulationManager::addElevatorRequest(ElevatorRequest *request)
{
    elevatorList->addRequest(request);
}

void SimulationManager::exitPerson(Person* person)
{
    if (currentTime >= 80.0)
    {
        waitTimeList.push_back(person->getTotalWaitTime());
    }

    delete person;
}
