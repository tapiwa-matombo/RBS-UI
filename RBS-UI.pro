#-------------------------------------------------
#
# Project created by QtCreator 2019-09-16T12:04:37
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RBS-UI
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
QT += sql widgets
QT += xml widgets
requires(qtConfig(tableview))

EXAMPLE_FILES = albumdetails.xml

SOURCES += \
        app-dialogs/audio-input-manager/audioinputmanager.cpp \
        app-dialogs/audio-processing/audioprocessing.cpp \
        app-dialogs/broadcast-manager/broadcastmanager.cpp \
        app-dialogs/playlist-builder/playlistbuilder.cpp \
        app-dialogs/playlist-manager/playlistmanager.cpp \
        app-dialogs/playlist-manager/playlistmanagerdialog.cpp \
        app-dialogs/program-scheduler/programscheduler.cpp \
        app-dialogs/settings-manager/settingsmanager.cpp \
        app-dialogs/tracks-manager/tracksmanager.cpp \
        app-dialogs/users-manager/usersmanager.cpp \
        audiorecorder.cpp \
        db/dba.cpp \
        main.cpp \
        models/librariestreemodel.cpp \
        models/librarymodel.cpp \
        models/tree-model/treemodel.cpp \
        models/treeitem.cpp \
        players/player.cpp \
        rbs.cpp \
        ui-components/Buttons/volumebutton.cpp \
        ui-components/library/library.cpp

HEADERS += \
        app-dialogs/audio-input-manager/audioinputmanager.h \
        app-dialogs/audio-processing/audioprocessing.h \
        app-dialogs/broadcast-manager/broadcastmanager.h \
        app-dialogs/playlist-builder/playlistbuilder.h \
        app-dialogs/playlist-manager/playlistmanager.h \
        app-dialogs/playlist-manager/playlistmanagerdialog.h \
        app-dialogs/program-scheduler/programscheduler.h \
        app-dialogs/settings-manager/settingsmanager.h \
        app-dialogs/tracks-manager/tracksmanager.h \
        app-dialogs/users-manager/usersmanager.h \
        audiorecorder.h \
        db/dba.h \
        models/librariestreemodel.h \
        models/librarymodel.h \
        models/tree-model/treemodel.h \
        models/treeitem.h \
        players/player.h \
        rbs.h \
        ui-components/Buttons/volumebutton.h \
        ui-components/library/library.h

FORMS += \
        app-dialogs/audio-input-manager/audioinputmanager.ui \
        app-dialogs/audio-processing/audioprocessing.ui \
        app-dialogs/broadcast-manager/broadcastmanager.ui \
        app-dialogs/playlist-builder/playlistbuilder.ui \
        app-dialogs/program-scheduler/programscheduler.ui \
        app-dialogs/settings-manager/settingsmanager.ui \
        app-dialogs/tracks-manager/tracksmanager.ui \
        app-dialogs/users-manager/usersmanager.ui \
        rbs.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons/resources.qrc \
    masterdetail.qrc

DISTFILES += \
    albumdetails.xml \

RC_ICONS = Excel.ico
