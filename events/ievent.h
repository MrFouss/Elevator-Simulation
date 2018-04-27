#ifndef IEVENT_H
#define IEVENT_H

class IEvent
{
protected:
    float triggerTime; // in seconds

public:
    IEvent(float triggerTime): triggerTime(triggerTime) {}
    ~IEvent() {}

    bool operator<(const IEvent& other) const;
    bool operator>(const IEvent& other) const;
    float getTriggerTime() const;
    virtual void resolve() = 0;
};

#endif // IEVENT_H
