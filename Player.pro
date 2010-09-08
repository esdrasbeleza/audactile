# -------------------------------------------------
# Project created by QtCreator 2010-05-03T16:01:44
# -------------------------------------------------
QT += sql \
    phonon \
    xml \
    xmlpatterns \
    network \
    webkit
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
    src/iconfactory.cpp \
    src/separator.cpp \
    src/mainwindow/mainnotebook/context/lyricswidget.cpp \
    src/mainwindow/mainnotebook/context/artistinfowidget.cpp \
    src/mainwindow/mainnotebook/context/contextwidget.cpp \
    src/services/lyricsdownloader.cpp \
    src/mainwindow/mainnotebook/context/abstractcontainer.cpp \
    src/settings/contextsettings.cpp \
    src/settings/settingsdialog/widgets/contextsettingswidget.cpp \
    src/music.cpp \
    src/collection/collectiondatabase.cpp \
    src/collection/collectionservice.cpp \
    src/mainwindow/mainnotebook/collection/collectiontreeview.cpp
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
    src/iconfactory.h \
    src/separator.h \
    src/mainwindow/mainnotebook/context/lyricswidget.h \
    src/mainwindow/mainnotebook/context/artistinfowidget.h \
    src/mainwindow/mainnotebook/context/contextwidget.h \
    src/services/lyricsdownloader.h \
    src/mainwindow/mainnotebook/context/abstractcontainer.h \
    src/services/collectionservice.h \
    src/settings/contextsettings.h \
    src/settings/settingsdialog/widgets/contextsettingswidget.h \
    src/music.h \
    src/collection/collectiondatabase.h \
    src/collection/collectionservice.h \
    src/mainwindow/mainnotebook/collection/collectiontreeview.h
RESOURCES = extra_images.qrc
win32|macx:RESOURCES += icons.qrc
CONFIG += link_pkgconfig
PKGCONFIG += taglib
OTHER_FILES += README
