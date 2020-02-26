#include "playlist.h"

#include <QMediaPlaylist>

Playlist::Playlist(QMediaPlaylist *parent):
    QMediaPlaylist(parent)
{
    //TODO: Initialize object

}


bool Playlist::addTracks(QUrl &url)
{
    if (addMedia(url))
        return true;
    return false;
}

bool Playlist::removeTracks(int start, int end)
{
    if(!(start < -1))
    {
      removeMedia(start, end);
      return true;
    }
    return false;
}

bool Playlist::removeTrack(int pos)
{
    if (pos > -1)
    {
        removeMedia(pos);
        return true;
    }
    return  false;
}

void shuffleTracks(Playlist *playlist)
{
    playlist->QMediaPlaylist::shuffle();
}

QMediaContent Playlist::selectTrack()
{
   QMediaContent track = QMediaPlaylist::currentMedia();
   return track;
}

void Playlist::goToEnd(Playlist *playlist)
{
    int count = playlist->mediaCount();
    playlist->setCurrentIndex(count);
}

void Playlist::goToStart(Playlist *playlist)
{
    int start = 0;
    playlist->setCurrentIndex(start);
}

bool Playlist::savePlaylist(Playlist *playlist,QUrl location)
{
    playlist->save(location);
    return true;
}

void Playlist::clearPlaylist(Playlist *playlist)
{
   playlist->clear();
}

void Playlist::nextPlaylist(Playlist *playlist)
{
    playlist->next();
}

void Playlist::prevPlaylist(Playlist *playlist)
{
    playlist->nextIndex();
}

void Playlist::showTrackInfo(Playlist *playlist, int currentIndex)
{
   playlist->media(currentIndex);
}

void Playlist::nextTrack(Playlist *playlist)
{
    playlist->nextIndex();
}

void Playlist::prevTrack(Playlist *playlist)
{
    playlist->previousIndex();
}

void Playlist::setCurrentTrack(Playlist *playlist, int index)
{
    playlist->setCurrentIndex(index);
}

void Playlist::setCurrentList(Playlist *playlist)
{
    playlist->currentMedia().playlist();
}
