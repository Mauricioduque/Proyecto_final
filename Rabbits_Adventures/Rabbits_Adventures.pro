QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aguila.cpp \
    cerdoenemigo.cpp \
    flag.cpp \
    fondo.cpp \
    gameover.cpp \
    inicio.cpp \
    jabalienemigo.cpp \
    lechuga.cpp \
    main.cpp \
    mainwindow.cpp \
    muros.cpp \
    murosnota.cpp \
    pina.cpp \
    ppconejo.cpp \
    primermundo.cpp \
    puntaje.cpp \
    roca.cpp \
    vidas.cpp \
    view.cpp \
    zanahoria.cpp

HEADERS += \
    aguila.h \
    cerdoenemigo.h \
    flag.h \
    fondo.h \
    gameover.h \
    inicio.h \
    jabalienemigo.h \
    lechuga.h \
    mainwindow.h \
    muros.h \
    murosnota.h \
    pina.h \
    ppconejo.h \
    primermundo.h \
    puntaje.h \
    roca.h \
    vidas.h \
    view.h \
    zanahoria.h

FORMS += \
    gameover.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Imagenes/imagenes.qrc

DISTFILES +=
