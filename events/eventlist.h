#ifndef EVENTLIST_H
#define EVENTLIST_H

#include<vector>

#include "ievent.h"

class EventList
{
private:
    std::vector<IEvent*> list;

public:
    EventList();
    ~EventList();

    void add(IEvent* newElement);
    IEvent* pop();
    void empty();
    bool isEmpty() const;
    float getNextEventTime() const;
};

#endif // EVENTLIST_H
