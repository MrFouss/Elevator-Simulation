#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

#include "data/enum.h"

class Configuration
{
private:
    float endOfSimulationTime = 43200.0;

    int amountFloors = 7;
    int amountElevators = 2;

    float meanPoissonPersonArrival = 0.5;
    float meanExponentialWorkTime = 60.0;

    BusyScheduling busyScheduling = BusyScheduling::LINEAR_SCAN;
    IdleScheduling idleScheduling = IdleScheduling::BOTTOM;

public:
    Configuration() {}
    void setup(const char configFilePath[] = ":/configuration/default");

    void printConfigurationSettings();

    float getEndOfSimulationTime();

    int getAmountFloors();
    int getAmountElevators();

    float getMeanPoissonPersonArrival();
    float getMeanExponentialWorkTime();

    BusyScheduling getBusyScheduling();
    IdleScheduling getIdleScheduling();
};

#endif // CONFIGURATION_H
