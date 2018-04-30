#include <QDebug>
#include <QDomDocument>
#include <QFile>

#include "configuration.h"

Configuration::Configuration()
{
    QFile file("config.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qFatal("Failed to open file for reading.");
        return;
    }

    QDomDocument document;
    if(!document.setContent(&file))
    {
        qFatal("Failed to parse the file into a DOM tree.");
        file.close();
        return;
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
        else if (element.attribute("key") == "meanExponentialWorkTime")
        {
            meanExponentialWorkTime = element.text().toFloat();
        }
        else if (element.attribute("key") == "busyScheduling")
        {
            if (element.text() == "SHORTEST_SEEK_TIME_FIRST")
            {
                busyScheduling = BusyScheduling::SHORTEST_SEEK_TIME_FIRST;
            }
            else if (element.text() == "LINEAR_SCAN")
            {
                busyScheduling = BusyScheduling::LINEAR_SCAN;
            }
        }
        else if (element.attribute("key") == "idleScheduling")
        {
            if (element.text() == "TOP")
            {
                idleScheduling = IdleScheduling::TOP;
            }
            else if (element.text() == "BOTTOM")
            {
                idleScheduling = IdleScheduling::BOTTOM;
            }
        }
    }
}

Configuration* Configuration::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Configuration();
    }

    return instance;
}

void Configuration::deleteInstance()
{
    delete instance;
    instance = nullptr;
}

void Configuration::printConfigurationSettings()
{
    qInfo().nospace().noquote() << "CONFIGURATION SETTINGS:";
    qInfo().nospace().noquote() << " - endOfSimulationTime: " << endOfSimulationTime;
    qInfo().nospace().noquote() << " - amountFloors: " << amountFloors;
    qInfo().nospace().noquote() << " - amountElevators: " << amountElevators;
    qInfo().nospace().noquote() << " - meanPoissonPersonArrival: " << meanPoissonPersonArrival;

    QDebug busySchedulingDebug = qInfo().nospace().noquote() << " - busyScheduling: ";
    switch (busyScheduling)
    {
    case BusyScheduling::SHORTEST_SEEK_TIME_FIRST:
        busySchedulingDebug << "SHORTEST_SEEK_TIME_FIRST";
        break;
    case BusyScheduling::LINEAR_SCAN:
        busySchedulingDebug << "LINEAR_SCAN";
        break;
    default:
        busySchedulingDebug << "UNKNOWN";
        break;
    }

    QDebug idleSchedulingDebug = qInfo().nospace().noquote() << " - idleScheduling: ";
    switch (idleScheduling)
    {
    case IdleScheduling::TOP:
        idleSchedulingDebug << "TOP";
        break;
    case IdleScheduling::BOTTOM:
        idleSchedulingDebug << "BOTTOM";
        break;
    default:
        idleSchedulingDebug << "UNKNOWN";
        break;
    }
}

float Configuration::getEndOfSimulationTime()
{
    return endOfSimulationTime;
}

int Configuration::getAmountFloors()
{
    return amountFloors;
}

int Configuration::getAmountElevators()
{
    return amountElevators;
}

float Configuration::getMeanPoissonPersonArrival()
{
    return meanPoissonPersonArrival;
}

float Configuration::getMeanExponentialWorkTime()
{
    return meanExponentialWorkTime;
}

BusyScheduling Configuration::getBusyScheduling()
{
    return busyScheduling;
}

IdleScheduling Configuration::getIdleScheduling()
{
    return idleScheduling;
}
