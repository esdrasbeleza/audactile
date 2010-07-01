# -------------------------------------------------
# Project created by QtCreator 2010-05-03T16:01:44
# -------------------------------------------------
QT += sql \
    phonon \
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
    src/mainwindow/mainwidget.cpp \
    src/main.cpp \
    src/settings/applicationsettings.cpp \
    src/settings/settingsdialog.cpp
HEADERS += src/mainwindow/mainnotebook/collection/collectiontreewidget.h \
    src/mainwindow/mainnotebook/filesystem/filesystemwidget.h \
    src/mainwindow/mainnotebook/mainnotebook.h \
    src/mainwindow/playlist/playlistwidget.h \
    src/mainwindow/playlist/playlistitem.h \
    src/mainwindow/playerbar.h \
    src/mainwindow/mainwindow.h \
    src/mainwindow/mainwidget.h \
    src/settings/applicationsettings.h \
    src/settings/settingsdialog.h
FORMS += 
OTHER_FILES += TODO.txt
