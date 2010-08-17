#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QSplitter>
#include "mainnotebook/mainnotebook.h"
#include <phonon/MediaObject>
#include <phonon/AudioOutput>
#include "playlist/playlistwidget.h"
#include "playerbar.h"
#include "../services/lastfmscrobbler.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    PlaylistWidget *playlistWidget;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;

private:
    Qt::WindowStates originalWindowState;
    qreal outputVolume;
    MainNotebook *mainNotebook;
    QSplitter *middleSplitter;
    void keyPressEvent(QKeyEvent *event);
    void toggleFullscreen();

private slots:
    void handleMute(bool mute);
    void handleVolume(qreal volume);
    void saveSplitterSize(int pos, int index);

};

#endif // MAINWINDOW_H
