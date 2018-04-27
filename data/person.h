#ifndef PERSON_H
#define PERSON_H

class Person
{
private:
    static inline int idCount = 0;
    int id;

    float waitStartTime = -1.0;
    float totalWaitTime = 0.0;
    int targetFloor;

public:
    Person();
    ~Person() {}

    void startWaitingElevator(float time);
    void endWaitingElevator(float time);
};

#endif // PERSON_H
