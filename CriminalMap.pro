#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T19:39:34
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CriminalMap
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
   src/main.cc \
    src/gui/windows/mainwindow.cc \
    src/gui/components/panelmain.cc \
    src/gui/components/panelmap.cc \
    src/gui/components/paneloptions.cc

HEADERS += \
   src/base/base.hh \
   src/core/core.hh \
   src/gui/gui.hh \
    src/gui/windows/mainwindow.hh \
    src/gui/components/panelmain.hh \
    src/gui/components/panelmap.hh \
    src/gui/components/paneloptions.hh
