QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$[QT_INSTALL_PREFIX]/src/qtbase/include/QtZlib

QMAKE_CXXFLAGS += -lzlibstat

win32{
INCLUDEPATH += $$[_PRO_FILE_PWD_]/zlib/static32/
LIBS += -lz
}

unix{
INCLUDEPATH +=/usr/lib
LIBS += /usr/lib/zlib/static32
}

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        aes/aes.c \
        cipher.cpp \
        cli_param.cpp \
        main.cpp \
        mini_ungzip/mini_gzip.c \
        mini_ungzip/miniz.c \
        parcel.cpp \
        qt_gzip/qcompressor.cpp \
        qt_gzip/qt_gzip_demo.cpp \
        zip.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    aes/aes.h \
    cipher.h \
    cli_param.h \
    mini_ungzip/mini_gzip.h \
    mini_ungzip/miniz.h \
    parcel.h \
    qt_gzip/qcompressor.h \
    zip.h
