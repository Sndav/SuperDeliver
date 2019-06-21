#-------------------------------------------------
#
# Project created by QtCreator 2019-06-08T10:31:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = deli
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        lib/IO/input.hpp \
        lib/IO/output.hpp \
        lib/algorithm/Assign.hpp \
        lib/algorithm/Path.hpp \
        lib/baseFunction/Bill.hpp \
        lib/baseFunction/Rider.hpp \
        lib/baseStructure/Algorithm.hpp \
        lib/baseStructure/Bill.hpp \
        lib/baseStructure/Rider.hpp \
        lib/baseStructure/Structure.hpp \
        lib/global/Consts.hpp \
        lib/global/Header.hpp \
        lib/global/Vars.hpp \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    imgsrc/bd.png \
    imgsrc/bg.png \
    imgsrc/road.png

RESOURCES += \
    img.qrc
