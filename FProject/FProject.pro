TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    textextractor.cpp \
    podofotexextract.cpp \
    dsstring.cpp

LIBS += -lpodofo

HEADERS += \
    textextractor.h \
    dsstring.h
