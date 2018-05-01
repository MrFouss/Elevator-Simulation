TEMPLATE = app
QT += core xml
QT -= gui
CONFIG += console c++11
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    singleton/simulationmanager.cpp \
    events/ievent.cpp \
    events/personarrivalevent.cpp \
    events/eventlist.cpp \
    data/person.cpp \
    events/callelevatorevent.cpp \
    events/arrivalatfloorevent.cpp \
    data/elevatorrequest.cpp \
    data/elevatorlist.cpp \
    singleton/configuration.cpp \
    events/exportdataevent.cpp \
    data/elevator/sstfelevator.cpp \
    data/elevator/linearscanelevator.cpp \
    data/elevator/abstractelevator.cpp

HEADERS += \
    singleton/simulationmanager.h \
    events/ievent.h \
    events/eventlist.h \
    events/personarrivalevent.h \
    data/person.h \
    events/callelevatorevent.h \
    events/arrivalatfloorevent.h \
    data/elevatorrequest.h \
    data/elevatorlist.h \
    singleton/configuration.h \
    data/enum.h \
    events/exportdataevent.h \
    data/elevator/sstfelevator.h \
    data/elevator/linearscanelevator.h \
    data/elevator/abstractelevator.h

QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES += \
    resources.qrc
