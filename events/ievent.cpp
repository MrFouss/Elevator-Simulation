#include "ievent.h"

bool IEvent::operator<(const IEvent& other) const
{
    return this->triggerTime < other.triggerTime;
}

float IEvent::getTriggerTime() const
{
    return this->triggerTime;
}
