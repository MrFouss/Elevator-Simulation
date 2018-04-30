#ifndef EVENTLIST_H
#define EVENTLIST_H

#include<vector>

#include "ievent.h"

class EventList
{
private:
    std::vector<IEvent*> list;

    void clear();

public:
    EventList() {}
    ~EventList();

    void add(IEvent* newElement);
    IEvent* pop();
    bool isEmpty() const;
    float getNextEventTime() const;
};

#endif // EVENTLIST_H
