#ifndef COLLECTIONITEM_H
#define COLLECTIONITEM_H

#include <QObject>
#include <QFileInfo>
#include <QUrl>
#include <phonon/MediaSource>
#include <phonon/MediaObject>
#include <phonon/AudioOutput>

class CollectionItem : public QObject
{
Q_OBJECT
public:
    explicit CollectionItem(QString filePath, QObject *parent = 0);
    QString getArtist();

private:
    Phonon::MediaObject *metaDataResolver;
    QString filePath;
    QString fileName;
    QString artist;
    QString title;
    QString album;

signals:
    void validFile(CollectionItem*);
    void invalidFile(CollectionItem*);

private slots:
    void loadMetaData(Phonon::State newState);

};

#endif // COLLECTIONITEM_H
