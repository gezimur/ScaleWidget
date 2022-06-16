QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH +=  $$PWD/../boost_1_76_0/

LIBS += -L$$PWD/../boost_1_76_0/lib

SOURCES += \
    ScaleCalculator.cpp \
    ScaleWidget_staff.cpp \
    TimeRange.cpp \
    main.cpp \
    ScaleWidget.cpp

HEADERS += \
    ScaleCalculator.h \
    ScaleWidget.h \
    ScaleWidget_staff.h \
    TimeRange.h

