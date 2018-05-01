#include <cmath>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QDebug>

#include "singleton/simulationmanager.h"
#include "singleton/configuration.h"

SimulationManager::SimulationManager()
{
    qDebug().nospace().noquote() << "Initialization of the simulation manager...";

    Configuration::getInstance()->printConfigurationSettings();

    elevatorList = new ElevatorList();

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
    delete instance;
    instance = nullptr;
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
    return !eventList.isEmpty() && eventList.getNextEventTime() <= Configuration::getInstance()->getEndOfSimulationTime();
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

AbstractElevator* SimulationManager::getIdleElevator()
{
    return elevatorList->getIdleElevator();
}

void SimulationManager::addElevatorRequest(ElevatorRequest *request)
{
    elevatorList->addRequest(request);
}

void SimulationManager::exitPerson(Person* person)
{
    if (currentTime >= 0.0)
    {
        waitTimeList.push_back(person->getTotalWaitTime());
    }

    delete person;
}
