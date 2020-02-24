#ifndef PLAYLISTBUILDER_H
#define PLAYLISTBUILDER_H

#include "db/dba.h"

#include <QWidget>
#include <QModelIndex>
#include <QMediaPlaylist>
#include <QTableWidgetItem>
#include <QMediaPlayer>
#include <QtSql>


QT_BEGIN_NAMESPACE
class QTreeView;
class QLabel;
class QTableView;
class QListWidget;
class QSqlRelationalTableModel;
class QFile;
class QGroupBox;
class QComboBox;
QT_END_NAMESPACE

namespace Ui {
class PlaylistBuilder;
}

class PlaylistBuilder : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistBuilder(QWidget *parent = nullptr);
    ~PlaylistBuilder();

    void addItemsToTable(QFileInfo fi);

public slots:
    void addDirectory();
    void addFile();

    void playUrl(const QUrl& url);
    void savePlaylist();
    void createPlaylist();
    bool loadPlaylist(QUrl location);
    void getMetaFileMetadata(QList<QUrl> files);

    void data();

    void onFileSelected();
    void onDirectorySelected();

    void setTableWidgetDnD();

private slots:
    void on_btnSavePlaylist_clicked();

    void on_btnPlaySample_clicked();

    void on_btnAddFolder_clicked();

    void on_btnRepeat_clicked();

    void on_tblSongsTable_itemClicked(QTableWidgetItem *item);

    void on_btnNext_clicked();

    void on_btnPrevious_clicked();

    void on_btnAddFile_clicked();

    void on_tblSongsTable_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::PlaylistBuilder *ui;
    QMediaPlayer *player = new QMediaPlayer();
    QMediaPlaylist *playlist = new QMediaPlaylist(player);
    //QString fileName;
};

#endif // PLAYLISTBUILDER_H
