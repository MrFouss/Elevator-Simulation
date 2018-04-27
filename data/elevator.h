#ifndef ELEVATOR_H
#define ELEVATOR_H


class Elevator
{
private:
    int currentFloor = 1;
    int targetFloor = 1;
    bool idle = true;

public:
    Elevator();

    bool isIdle();
};

#endif // ELEVATOR_H
