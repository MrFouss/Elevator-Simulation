#ifndef EXPORTDATAEVENT_H
#define EXPORTDATAEVENT_H

#include "ievent.h"

class ExportDataEvent : public IEvent
{
public:
    ExportDataEvent(float triggerTime) : IEvent(triggerTime) {}

    virtual void resolve();
};

#endif // EXPORTDATAEVENT_H
