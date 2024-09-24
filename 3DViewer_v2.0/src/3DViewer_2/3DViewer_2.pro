QT       += core gui opengl

include(model/3rdparty/qtgifimage/src/gifimage/qtgifimage.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

# Добавление зависимостей для Windows
win32: {
    LIBS += -lopengl32
    LIBS += -lglu32
}

CONFIG += c++17

SOURCES += \
    controller/controller.cc \
    main.cc \
    model/colorbuttons.cc \
    model/model.cpp \
    model/objreader.cc \
    model/opengl_widget_class.cc \
    model/record_functions.cc \
    model/shift_scale_rotation.cc \
    view/view.cc

HEADERS += \
    controller/controller.h \
    model/model.h \
    model/my_functions.h \
    model/opengl_widget_class.h \
    view/ui_view.h \
    view/view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
