RC_ICONS = farmer.ico

QT += sql
QT       += core gui multimedia
#加入multimedia才能设置音效因为QT6不支持所以降版本为QT5

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battle.cpp \
    battle2.cpp \
    battle3.cpp \
    doge.cpp \
    egg.cpp \
    fruit.cpp \
    hen.cpp \
    henhouse.cpp \
    main.cpp \
    mainwindow.cpp \
    moon.cpp \
    sky.cpp \
    sun.cpp \
    tree.cpp \
    wheat.cpp

HEADERS += \
    battle.h \
    battle2.h \
    battle3.h \
    doge.h \
    egg.h \
    fruit.h \
    hen.h \
    henhouse.h \
    mainwindow.h \
    moon.h \
    sky.h \
    sun.h \
    tree.h \
    wheat.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    res/battle3.png
