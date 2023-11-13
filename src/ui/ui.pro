QT       += core gui
QT += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/facade/facade.cc \
    ../model/figure/figure.cc \
    ../model/parser/parser.cc \
    main.cc \
    mainwindow.cc \
    openglgraphics.cc \
    src/3rdParty/giflib/dgif_lib.c \
    src/3rdParty/giflib/egif_lib.c \
    src/3rdParty/giflib/gif_err.c \
    src/3rdParty/giflib/gif_font.c \
    src/3rdParty/giflib/gif_hash.c \
    src/3rdParty/giflib/gifalloc.c \
    src/3rdParty/giflib/quantize.c \
    src/gifimage/qgifimage.cpp

HEADERS += \
    ../controller/controller.h \
    ../model/facade/facade.h \
    ../model/figure/figure.h \
    ../model/parser/parser.h \
    mainwindow.h \
    openglgraphics.h \
    src/3rdParty/giflib/gif_hash.h \
    src/3rdParty/giflib/gif_lib.h \
    src/3rdParty/giflib/gif_lib_private.h \
    src/gifimage/qgifglobal.h \
    src/gifimage/qgifimage.h \
    src/gifimage/qgifimage_p.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../icons/home.png \
    ../models/Energy_rocket.obj \
    ../models/Skull_v3.obj \
    ../models/simple_cube.obj \
    ../models/skull.obj \
    ../models/teapot.obj \
    ../models/teddy.obj \
    ../models/woman.obj \
    icons/cube.gif

RESOURCES += \
    resources.qrc

SUBDIRS += \
    src/gifimage/gifimage.pro
