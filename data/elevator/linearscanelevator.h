#ifndef LINEARSCANELEVATOR_H
#define LINEARSCANELEVATOR_H

#include "data/elevator/abstractelevator.h"

class LinearScanElevator : public AbstractElevator
{
private:
    Direction direction = Direction::UP;

    void invertDirection();
    bool isFloorInRightDirection(int floor);

public:
    LinearScanElevator(ElevatorList* elevatorList) : AbstractElevator(elevatorList) {}

    virtual void embark();
    virtual int chooseFloor();
};

#endif // LINEARSCANELEVATOR_H
