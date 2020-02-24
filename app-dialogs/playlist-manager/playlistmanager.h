#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QMainWindow>
#include <QtXml/QDomDocument>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
class QComboBox;
class QFile;
class QGroupBox;
class QLabel;
class QListWidget;
class QSqlRelationalTableModel;
class QTableView;
QT_END_NAMESPACE

class PlaylistManager: public QMainWindow
{
    Q_OBJECT

    public:
        PlaylistManager(const QString &artistTable, const QString &albumTable,
                        QFile *albumDetails, QWidget *parent = nullptr);

    private slots:
        void about();
        void addAlbum();
        void changeArtist(int row);
        void deleteAlbum();
        void showAlbumDetails(QModelIndex index);
        void showArtistProfile(QModelIndex index);
        void updateHeader(QModelIndex, int, int);

    private:
        void adjustHeader();
        QGroupBox *createAlbumGroupBox();
        QGroupBox *createArtistGroupBox();
        QGroupBox *createDetailsGroupBox();
        void createMenuBar();
        void decreaseAlbumCount(QModelIndex artistIndex);
        void getTrackList(QDomNode album);
        QModelIndex indexOfArtist(const QString &artist);
        void readAlbumData();
        void removeAlbumFromDatabase(QModelIndex album);
        void removeAlbumFromFile(int id);
        void showImageLabel();

        QTableView *albumView;
        QComboBox *artistView;
        QListWidget *trackList;

        QLabel *iconLabel;
        QLabel *imageLabel;
        QLabel *profileLabel;
        QLabel *titleLabel;

        QDomDocument albumData;
        QFile *file;
        QSqlRelationalTableModel *model;
};

#endif // PLAYLISTMANAGER_H
