#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T10:26:25
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SWAN2
TEMPLATE = app

#DESTDIR=bin
#OBJECTS_DIR = build
#MOC_DIR = build

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
    EntityViewWidget.cpp \
    NNViewWidget.cpp \
    Vegetal.cpp \
    Water.cpp \
    EntityFrame.cpp \
    EntityAttributeWidget.cpp \
    Resource.cpp \
    Meat.cpp \
    Herbivore.cpp \
    Carnivore.cpp \
    WorldCreator.cpp \
    WorldCreatorResourcesWidget.cpp \
    WorldCreatorAnimalsWidget.cpp \
    Timelinewidget.cpp \
    qcustomplot.cpp \
    WorldEditor.cpp \
    config/config.cpp \
    ParametersWidget.cpp \
    WorldEditorToolBox.cpp

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
    SaveManager.h \
    config/errors.h \
    config/config.h \
    config/nnNames.h \
    EntityViewWidget.h \
    Vegetal.h \
    Water.h \
    EntityFrame.h \
    EntityAttributeWidget.h \
    NNViewWidget.h \
    Resource.h \
    Meat.h \
    VisionSector_NonLiving.h \
    VisionSector_Living.h \
    Herbivore.h \
    Carnivore.h \
    WorldCreator.h \
    WorldCreatorResourcesWidget.h \
    WorldCreatorAnimalsWidget.h \
    Timelinewidget.h \
    qcustomplot.h \
    WorldEditor.h \
    ParametersWidget.h \
    WorldEditorToolBox.h

FORMS    += mainwindow.ui \
    WorldCreator.ui \
    WorldCreatorResourcesWidget.ui \
    WorldCreatorAnimalsWidget.ui \
    Timelinewidget.ui \
    ParametersWidget.ui \
    WorldEditorToolBox.ui
