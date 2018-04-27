TEMPLATE = app
QT += xml
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
    simulationmanager.cpp \
    events/ievent.cpp \
    events/personarrivalevent.cpp \
    events/eventlist.cpp \
    data/person.cpp \
    data/elevator.cpp

HEADERS += \
    simulationmanager.h \
    events/ievent.h \
    events/eventlist.h \
    events/personarrivalevent.h \
    data/person.h \
    data/elevator.h

QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES += \
    resources.qrc
