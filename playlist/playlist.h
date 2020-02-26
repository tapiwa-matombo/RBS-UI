#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QMediaPlaylist>

class Playlist: public QMediaPlaylist
{
    Q_OBJECT

    public:
       explicit Playlist( QMediaPlaylist *parent = nullptr);

       static QStringList playlists();

    signals:


    public slots:
       bool addTracks(QUrl &url);
       bool removeTracks(int start, int end);
       bool removeTrack(int pos);
       void shuffleTracks(Playlist *playlist);
       QMediaContent selectTrack();
       void goToEnd(Playlist *playlist);
       void goToStart(Playlist *playlist);
       bool savePlaylist(Playlist *playlist, QUrl location);
       void clearPlaylist(Playlist *playlist);
       void nextPlaylist(Playlist *playlist);
       void prevPlaylist(Playlist *playlist);
       void showTrackInfo(Playlist *playlist, int currentIndex);
       void nextTrack(Playlist *playlist);
       void prevTrack(Playlist *playlist);
       void setCurrentTrack(Playlist *playlist, int index);
       void setCurrentList(Playlist *playlist);

    protected:
       bool event(QEvent *event) override;
};

#endif // PLAYLIST_H
