QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# Вы можете заставить ваш код не компилироваться, если он использует устаревшие API.
# Для этого раскомментируйте следующую строку.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # отключает все API, устаревшие до Qt 6.0.0

CONFIG += static

SOURCES += \
    CFunctions/calcExpr.c \
    CFunctions/credit.c \
    CFunctions/depositV2.c \
    CFunctions/parcerRPN.c \
    creditwindow.cpp \
    depositwindow.cpp \
    main.cpp \
    plotwindow.cpp \
    qcustomplot.cpp \
    smartcalc.cpp

HEADERS += \
    CHeader.h \
    creditwindow.h \
    depositwindow.h \
    plotwindow.h \
    qcustomplot.h \
    smartcalc.h

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    plotwindow.ui \
    smartcalc.ui

# Установите каталог сборки рядом с каталогом проекта
DESTDIR = $$PWD/../build
TARGET = SmartCalc

# Правила по умолчанию для развертывания.
unix {
    # Укажите пути для платформы Unix (включая Linux и macOS).
    target.path = /opt/$${TARGET}/bin
} else:win32 {
    # Укажите пути для платформы Windows.
    target.path = /tmp/$${TARGET}/bin
}

!isEmpty(target.path): INSTALLS += target


#QT += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

#CONFIG += c++17

## Uncomment the following line to disable deprecated APIs before Qt 6.0.0.
## DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

#CONFIG += static

#SOURCES += \
#    CFunctions/calcExpr.c \
#    CFunctions/credit.c \
#    CFunctions/depositV2.c \
#    CFunctions/parcerRPN.c \
#    creditwindow.cpp \
#    depositwindow.cpp \
#    main.cpp \
#    plotwindow.cpp \
#    qcustomplot.cpp \
#    smartcalc.cpp

#HEADERS += \
#    CHeader.h \
#    creditwindow.h \
#    depositwindow.h \
#    plotwindow.h \
#    qcustomplot.h \
#    smartcalc.h

#FORMS += \
#    creditwindow.ui \
#    depositwindow.ui \
#    plotwindow.ui \
#    smartcalc.ui

## Set the build directory next to the project directory
#DESTDIR = $$PWD/../build
#TARGET = SmartCalc

## Default deployment directory for Unix
#unix {
#    target.path = /opt/$${TARGET}/bin
#}

## Default deployment directory for Windows
#win32 {
#    target.path = /tmp/$${TARGET}/bin
#}

## Install the target to the specified path
#!isEmpty(target.path): INSTALLS += target

## Custom target for deploying on Windows
#win32 {
#    # Define a new target called "deploy"
#    deploy.path = $$OUT_PWD
#    deploy.commands = $$[QT_INSTALL_BINS]/windeployqt --release --no-translations --no-openglsw $${OUT_PWD}/$${TARGET}.exe
#    QMAKE_EXTRA_TARGETS += deploy

#    # Ensure "deploy" is run after the "all" target
#    PRE_TARGETDEPS += deploy
#}
