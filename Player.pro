# -------------------------------------------------
# Project created by QtCreator 2010-05-03T16:01:44
# -------------------------------------------------
QT += sql \
    phonon \
    xml \
    xmlpatterns \
    network
TARGET = Player
TEMPLATE = app
SOURCES += src/mainwindow/mainnotebook/collection/collectiontreewidget.cpp \
    src/mainwindow/mainnotebook/filesystem/filesystemwidget.cpp \
    src/mainwindow/mainnotebook/mainnotebook.cpp \
    src/mainwindow/playlist/playlistwidget.cpp \
    src/mainwindow/playlist/playlistitem.cpp \
    src/mainwindow/playerbar.cpp \
    src/mainwindow/mainwindow.cpp \
    src/main.cpp \
    src/settings/applicationsettings.cpp \
    src/settings/settingsdialog/widgets/foldersettingswidget.cpp \
    src/settings/settingsdialog/settingsdialog.cpp \
    src/settings/settingsdialog/widgets/lastfmsettingswidget.cpp \
    src/settings/lastfmsettings.cpp \
    src/services/lastfmscrobbler.cpp \
    src/services/lastfmcontext.cpp \
    src/mainwindow/mainnotebook/context/contextwidget.cpp \
    src/iconfactory.cpp \
    src/collection/collectiondatabase.cpp \
    src/collection/collectionitem.cpp
HEADERS += src/mainwindow/mainnotebook/collection/collectiontreewidget.h \
    src/mainwindow/mainnotebook/filesystem/filesystemwidget.h \
    src/mainwindow/mainnotebook/mainnotebook.h \
    src/mainwindow/playlist/playlistwidget.h \
    src/mainwindow/playlist/playlistitem.h \
    src/mainwindow/playerbar.h \
    src/mainwindow/mainwindow.h \
    src/settings/applicationsettings.h \
    src/settings/settingsdialog/widgets/foldersettingswidget.h \
    src/settings/settingsdialog/settingsdialog.h \
    src/settings/settingsdialog/widgets/lastfmsettingswidget.h \
    src/settings/lastfmsettings.h \
    src/services/lastfmscrobbler.h \
    src/services/lastfmcontext.h \
    src/mainwindow/mainnotebook/context/contextwidget.h \
    src/iconfactory.h \
    src/collection/collectiondatabase.h \
    src/collection/collectionitem.h
FORMS += 
RESOURCES += images.qrc
OTHER_FILES += README
