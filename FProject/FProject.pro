TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    documentparser.cpp \
    indexhandler.cpp \
    indexinterface.cpp \
    avltreeindex.cpp \
    searchengine.cpp

LIBS += -lpodofo

HEADERS += \
    textextractor.h \
    documentparser.h \
    english_stem.h \
    stemming.h \
    common_lang_constants.h \
    string_util.h \
    debug_logic.h \
    utilities.h \
    safe_math.h \
    indexhandler.h \
    avltreeindex.h \
    searchengine.h
