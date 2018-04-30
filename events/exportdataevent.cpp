#include <QTextStream>
#include <QFile>

#include "exportdataevent.h"
#include "simulationmanager.h"

void ExportDataEvent::resolve()
{
    QFile csvFile("result_simulation.csv");

    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream out(&csvFile);
        out << triggerTime << ", " << SimulationManager::getInstance()->getAverageWaitTime() << "\n";
        csvFile.close();
    }

    SimulationManager::getInstance()->addEvent(new ExportDataEvent(triggerTime + 1.0));
}
