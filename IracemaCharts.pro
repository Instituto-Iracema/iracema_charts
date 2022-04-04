TEMPLATE = lib
TARGET = IracemaCharts
QT += qml quick
CONFIG += plugin c++11 qmltypes

QML_IMPORT_NAME = IracemaCharts
QML_IMPORT_MAJOR_VERSION = 0
QML_IMPORT_MINOR_VERSION = 1

TARGET = $$qtLibraryTarget($$TARGET)
uri = IracemaCharts

# Input
SOURCES += \
        LineSeries/iracemalineseries.cpp \
        iracemacharts_plugin.cpp \
        iracemacharts.cpp \
        LineSeries/iracemalineseriesview.cpp

HEADERS += \
        LineSeries/iracemalineseries.h \
        iracemacharts_plugin.h \
        iracemacharts.h \
        LineSeries/iracemalineseriesview.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

windows {
    installPath = $$[QT_INSTALL_QML]\$$replace(uri, \., \)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
