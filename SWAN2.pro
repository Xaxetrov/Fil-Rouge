#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T10:26:25
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWAN2
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Entity.cpp \
    World.cpp \
    Solid.cpp \
    Animal.cpp \
    NonSolid.cpp \
    Vision.cpp \
    Coordinate.cpp \
    WorldWidget.cpp \
    WorldColors.cpp \
    Neuron.cpp \
    NeuralNetwork.cpp \
    Neuronlayer.cpp \
    Percepted.cpp \
    Visionsector.cpp \
    Visionsector_Living.cpp \
    Visionsector_NonLiving.cpp \
    SaveManager.cpp \
    config.c

HEADERS  += mainwindow.h \
    Entity.h \
    World.h \
    Solid.h \
    Animal.h \
    NonSolid.h \
    Vision.h \
    Coordinate.h \
    WorldWidget.h \
    WorldColors.h \
    Neuron.h \
    Neuronlayer.h \
    NeuralNetwork.h \
    Percepted.h \
    Visionsector.h \
    Visionsector_Living.h \
    Visionsector_NonLiving.h \
    config.h \
    SaveManager.h

FORMS    += mainwindow.ui
