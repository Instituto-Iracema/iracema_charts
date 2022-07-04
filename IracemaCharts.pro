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
        iracemalineseries.cpp \
        iracemacharts_plugin.cpp \
        iracemacharts.cpp \
        iracemalineseriesview.cpp \
        iracemapointlabel.cpp \
        iracemascalelabel.cpp

HEADERS += \
        iracemalineseries.h \
        iracemacharts_plugin.h \
        iracemacharts.h \
        iracemalineseriesview.h \
        iracemapointlabel.h \
        iracemascalelabel.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
qmldir.files += plugins.qmltypes
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    copy_qmltypes.path = $$installPath
    copy_qmltypes.files = $$OUT_PWD/plugins.qmltypes
    INSTALLS += target qmldir copy_qmltypes
}

windows {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    installPath = $$replace(installPath, /, \\)
    qmldir.path = $$installPath
    target.path = $$installPath
    copy_qmltypes.path = $$installPath
    copy_qmltypes.files = $$OUT_PWD/plugins.qmltypes
    INSTALLS += target qmldir copy_qmltypes
}
