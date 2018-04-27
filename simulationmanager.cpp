#include <iostream>
#include <QFile>
#include <QXmlStreamReader>
#include <QDomDocument>

#include "simulationmanager.h"
SimulationManager::SimulationManager()
{
    qDebug("Initialization of the simulation manager...");

    QFile file(CONFIG_FILE_PATH);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("Failed to open file for reading.");
    }

    QDomDocument document;
    if(!document.setContent(&file))
    {
        qDebug("Failed to parse the file into a DOM tree.");
        file.close();
    }
    file.close();

    QDomNodeList dataElements = document.documentElement().elementsByTagName("data");

    for (int i = 0; i < dataElements.count(); ++i)
    {
        QDomElement element = dataElements.item(i).toElement();

        if (element.attribute("key") == "amountFloors")
        {
            amountFloors = element.text().toInt();
        }
        else if (element.attribute("key") == "amountElevators")
        {
            amountElevators = element.text().toInt();
        }
        else if (element.attribute("key") == "endOfSimulationTime")
        {
            endOfSimulationTime = element.text().toFloat();
        }
        else if (element.attribute("key") == "meanPoissonPersonArrival")
        {
            meanPoissonPersonArrival = element.text().toFloat();
        }
    }

    waitingForElevatorPeopleList = std::vector<std::vector<Person*>>(amountFloors);

    std::cout << "End of initialization of the simulation manager" << std::endl << std::endl;
}

SimulationManager::~SimulationManager()
{
    eventList.empty();

    for (int i = 0; i < amountFloors; ++i) {
        for (Person* person : waitingForElevatorPeopleList[i])
        {
            delete person;
        }
    }
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

void SimulationManager::printConfigurationSettings()
{
    std::cout << "CONFIGURATION SETTINGS:" << std::endl;
    std::cout << " - amountFloors: " << amountFloors << std::endl;
    std::cout << " - amountElevators: " << amountElevators << std::endl;
    std::cout << " - endOfSimulationTime: " << endOfSimulationTime << std::endl;
    std::cout << " - meanPoissonPersonArrival: " << meanPoissonPersonArrival << std::endl;
}

int SimulationManager::getAmountFloors()
{
    return amountFloors;
}

int SimulationManager::getAmountElevators()
{
    return amountElevators;
}

float SimulationManager::getMeanPoissonPersonArrival()
{
    return meanPoissonPersonArrival;
}

void SimulationManager::addEvent(IEvent* event)
{
    eventList.add(event);
}

bool SimulationManager::isNextEventSolvable()
{
    return !eventList.isEmpty() && eventList.getNextEventTime() <= endOfSimulationTime;
}

void SimulationManager::resolveNextEvent()
{
    IEvent* event = eventList.pop();
    event->resolve();
    delete event;
}

void SimulationManager::addPersonWaitingForElevator(int floor, Person* person)
{
    waitingForElevatorPeopleList[floor].push_back(person);
}
