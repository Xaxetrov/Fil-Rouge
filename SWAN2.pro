#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T10:26:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWAN2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Entity.cpp \
    World.cpp \
    Solid.cpp \
    Animal.cpp \
    AnimalVisionSector.cpp \
    NonSolid.cpp \
    VisionSector.cpp \
    Vision.cpp \
    Coordinate.cpp \
    Neuron.cpp \
    NeuralNetwork.cpp \
    Neuronlayer.cpp

HEADERS  += mainwindow.h \
    Entity.h \
    World.h \
    Solid.h \
    Animal.h \
    AnimalVisionSector.h \
    NonSolid.h \
    VisionSector.h \
    Vision.h \
    Coordinate.h \
    Neuron.h \
    Neuronlayer.h \
    NeuralNetwork.h

FORMS    += mainwindow.ui
