TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    indexhandler.cpp \
    avltreeindex.cpp \
    searchengine.cpp \
    textextractor.cpp \
    DocumentParser.cpp \
    indexextractor.cpp \
    hash.cpp \
    queryengine.cpp \
    rawoutputextractor.cpp

LIBS += -lpodofo

HEADERS += \
    textextractor.h \
    english_stem.h \
    stemming.h \
    common_lang_constants.h \
    string_util.h \
    debug_logic.h \
    utilities.h \
    safe_math.h \
    indexhandler.h \
    avltreeindex.h \
    searchengine.h \
    indexextractor.h \
    DocumentParser.h \
    indexinterface.h \
    hash.h \
    queryengine.h \
    rawoutputextractor.h
