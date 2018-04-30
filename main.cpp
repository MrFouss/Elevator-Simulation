#include <QDebug>
#include <QFile>
#include <QDir>

#include "simulationmanager.h"
#include "events/personarrivalevent.h"
#include "events/exportdataevent.h"

using namespace std;

int main()
{
    QFile csvFile("result_simulation.csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        csvFile.close();
    }

    qDebug().nospace().noquote() << "###########################";
    qDebug().nospace().noquote() << "# STARTING THE SIMULATION #";
    qDebug().nospace().noquote() << "###########################";

    SimulationManager* simulationManager = SimulationManager::getInstance();

    // initiate a first event to start the simulation
    simulationManager->addEvent(new PersonArrivalEvent(0.0));
    simulationManager->addEvent(new ExportDataEvent(100.0));

    while (simulationManager->isNextEventSolvable())
    {
        simulationManager->resolveNextEvent();
    }

    // destroy remaining objects
    SimulationManager::deleteInstance();

    return 0;
}
