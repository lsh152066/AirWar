QT       += core gui sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    configuration.cpp \
    enemybullet.cpp \
    enemyflight.cpp \
    main.cpp \
    mainwight.cpp \
    mybullet.cpp \
    myflight.cpp \
    nettransfrom.cpp \
    prop.cpp \
    rank.cpp \
    single_sql.cpp \
    wight.cpp

HEADERS += \
    NetDef.h \
    background.h \
    configuration.h \
    enemybullet.h \
    enemyflight.h \
    mainwight.h \
    mybullet.h \
    myflight.h \
    nettransfrom.h \
    prop.h \
    rank.h \
    single_sql.h \
    wight.h

FORMS += \
    mainwight.ui \
    rank.ui \
    wight.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
