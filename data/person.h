#ifndef PERSON_H
#define PERSON_H

class Person
{
private:
    static inline int idCount = 0;
    int id;

    float waitStartTime = -1.0;
    float totalWaitTime = 0.0;

    int currentFloor = 1;
    int targetFloor;

public:
    Person();
    ~Person() {}

    int getId();

    float getTotalWaitTime();

    int getCurrentFloor();
    void setCurrentFloor(int floor);

    int getTargetFloor();
    void setTargetFloor(int floor);

    void startWaitingElevator(float time);
    void endWaitingElevator(float time);
};

#endif // PERSON_H
