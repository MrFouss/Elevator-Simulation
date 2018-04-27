#include "eventlist.h"

EventList::EventList()
{

}

EventList::~EventList()
{
    empty();
}

void EventList::add(IEvent* newElement)
{
    std::vector<IEvent*>::iterator it = list.begin();
    bool isAdded = false;

    while (it < list.end() && !isAdded)
    {
        if (*newElement < **it)
        {
            list.insert(it, newElement);
            isAdded = true;
        }
        ++it;
    }

    if (!isAdded)
    {
        list.push_back(newElement);
    }
}

IEvent* EventList::pop()
{
    IEvent* element = list.front();
    list.erase(list.begin());
    return element;
}

void EventList::empty()
{
    std::vector<IEvent*>::iterator it;

    for (it = list.begin(); it < list.end(); ++it)
    {
        delete *it;
    }
}

bool EventList::isEmpty() const
{
    return list.empty();
}

float EventList::getNextEventTime() const
{
    return list.front()->getTriggerTime();
}
