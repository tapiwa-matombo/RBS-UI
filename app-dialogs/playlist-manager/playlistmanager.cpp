#include "playlistmanager.h"
#include "app-dialogs/playlist-manager/playlistmanagerdialog.h"

#include <QtWidgets>
#include <QtSql>
#include <QtXml/QDomDocument>

extern int uniqueAlbumId;
extern int uniqueArtistId;

PlaylistManager::PlaylistManager(const QString &artistTable, const QString &albumTable,
                        QFile *albumDetails, QWidget *parent)
        : QMainWindow(parent)
{
    file = albumDetails;
    readAlbumData();

    model = new QSqlRelationalTableModel(this);
    model->setTable(albumTable);
    model->setRelation(2, QSqlRelation(artistTable, "id", "artist"));
    model->select();

    QGroupBox *artists = createArtistGroupBox();
    QGroupBox *albums = createAlbumGroupBox();
    QGroupBox *details = createDetailsGroupBox();

    artistView->setCurrentIndex(0);
    uniqueAlbumId = model->rowCount();
    uniqueArtistId = artistView->count();

    connect(model, &QSqlRelationalTableModel::rowsInserted,
            this, &PlaylistManager::updateHeader);
    connect(model, &QSqlRelationalTableModel::rowsRemoved,
            this, &PlaylistManager::updateHeader);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(artists, 0, 0);
    layout->addWidget(albums, 1, 0);
    layout->addWidget(details, 0, 1, 2, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    createMenuBar();

    showImageLabel();
    resize(850, 400);
    setWindowTitle(tr("Music Archive"));
}

void PlaylistManager::changeArtist(int row)
{
    if (row > 0) {
        QModelIndex index = model->relationModel(2)->index(row, 1);
        model->setFilter("artist = '" + index.data().toString() + '\'') ;
        showArtistProfile(index);
    } else if (row == 0) {
        model->setFilter(QString());
        showImageLabel();
    } else {
        return;
    }
}

void PlaylistManager::showArtistProfile(QModelIndex index)
{
    QSqlRecord record = model->relationModel(2)->record(index.row());

    QString name = record.value("artist").toString();
    QString count = record.value("albumcount").toString();
    profileLabel->setText(tr("Artist : %1 \n" \
                             "Number of Albums: %2").arg(name).arg(count));

    profileLabel->show();
    iconLabel->show();

    titleLabel->hide();
    trackList->hide();
    imageLabel->hide();
}

void PlaylistManager::showAlbumDetails(QModelIndex index)
{
    QSqlRecord record = model->record(index.row());

    QString artist = record.value("artist").toString();
    QString title = record.value("title").toString();
    QString year = record.value("year").toString();
    QString albumId = record.value("albumid").toString();

    showArtistProfile(indexOfArtist(artist));
    titleLabel->setText(tr("Title: %1 (%2)").arg(title).arg(year));
    titleLabel->show();

    QDomNodeList albums = albumData.elementsByTagName("album");
    for (int i = 0; i < albums.count(); ++i) {
        QDomNode album = albums.item(i);
        if (album.toElement().attribute("id") == albumId) {
            getTrackList(album.toElement());
            break;
        }
    }
    if (trackList->count() != 0)
        trackList->show();
}

void PlaylistManager::getTrackList(QDomNode album)
{
    trackList->clear();

    QDomNodeList tracks = album.childNodes();
    QDomNode track;
    QString trackNumber;

    for (int i = 0; i < tracks.count(); ++i) {

        track = tracks.item(i);
        trackNumber = track.toElement().attribute("number");

        QListWidgetItem *item = new QListWidgetItem(trackList);
        item->setText(trackNumber + ": " + track.toElement().text());
    }
}

void PlaylistManager::addAlbum()
{
    PlaylistManagerDialog *dialog = new PlaylistManagerDialog(model, albumData, file, this);
    int accepted = dialog->exec();

    if (accepted == 1) {
        int lastRow = model->rowCount() - 1;
        albumView->selectRow(lastRow);
        albumView->scrollToBottom();
        showAlbumDetails(model->index(lastRow, 0));
    }
}

void PlaylistManager::deleteAlbum()
{
    QModelIndexList selection = albumView->selectionModel()->selectedRows(0);

    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        int id = idIndex.data().toInt();
        QString title = idIndex.sibling(idIndex.row(), 1).data().toString();
        QString artist = idIndex.sibling(idIndex.row(), 2).data().toString();

        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("Delete Album"),
                                       tr("Are you sure you want to "
                                          "delete '%1' by '%2'?")
                                       .arg(title, artist),
                                       QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {
            removeAlbumFromFile(id);
            removeAlbumFromDatabase(idIndex);
            decreaseAlbumCount(indexOfArtist(artist));

            showImageLabel();
        }
    } else {
        QMessageBox::information(this, tr("Delete Album"),
                                 tr("Select the album you want to delete."));
    }
}

void PlaylistManager::removeAlbumFromFile(int id)
{

    QDomNodeList albums = albumData.elementsByTagName("album");

    for (int i = 0; i < albums.count(); ++i) {
        QDomNode node = albums.item(i);
        if (node.toElement().attribute("id").toInt() == id) {
            albumData.elementsByTagName("archive").item(0).removeChild(node);
            break;
        }
    }
/*
    The following code is commented out since we are using an in
    memory database, i.e., altering the XML file will bring the data
    out of sync.

    if (!file->open(QIODevice::WriteOnly)) {
        return;
    } else {
        QTextStream stream(file);
        albumData.elementsByTagName("archive").item(0).save(stream, 4);
        file->close();
    }
*/
}

void PlaylistManager::removeAlbumFromDatabase(QModelIndex index)
{
    model->removeRow(index.row());
}

void PlaylistManager::decreaseAlbumCount(QModelIndex artistIndex)
{
    int row = artistIndex.row();
    QModelIndex albumCountIndex = artistIndex.sibling(row, 2);
    int albumCount = albumCountIndex.data().toInt();

    QSqlTableModel *artists = model->relationModel(2);

    if (albumCount == 1) {
        artists->removeRow(row);
        showImageLabel();
    } else {
        artists->setData(albumCountIndex, QVariant(albumCount - 1));
    }
}

void PlaylistManager::readAlbumData()
{
    if (!file->open(QIODevice::ReadOnly))
        return;

    if (!albumData.setContent(file)) {
        file->close();
        return;
    }
    file->close();
}

QGroupBox* PlaylistManager::createArtistGroupBox()
{
    artistView = new QComboBox;
    artistView->setModel(model->relationModel(2));
    artistView->setModelColumn(1);

    connect(artistView, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &PlaylistManager::changeArtist);

    QGroupBox *box = new QGroupBox(tr("Artist"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(artistView, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* PlaylistManager::createAlbumGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("Album"));

    albumView = new QTableView;
    albumView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    albumView->setSortingEnabled(true);
    albumView->setSelectionBehavior(QAbstractItemView::SelectRows);
    albumView->setSelectionMode(QAbstractItemView::SingleSelection);
    albumView->setShowGrid(false);
    albumView->verticalHeader()->hide();
    albumView->setAlternatingRowColors(true);
    albumView->setModel(model);
    adjustHeader();

    QLocale locale = albumView->locale();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    albumView->setLocale(locale);

    connect(albumView, &QTableView::clicked,
            this, &PlaylistManager::showAlbumDetails);
    connect(albumView, &QTableView::activated,
            this, &PlaylistManager::showAlbumDetails);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(albumView, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* PlaylistManager::createDetailsGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("Details"));

    profileLabel = new QLabel;
    profileLabel->setWordWrap(true);
    profileLabel->setAlignment(Qt::AlignBottom);

    titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignBottom);

    iconLabel = new QLabel();
    iconLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    iconLabel->setPixmap(QPixmap(":/images/icon.png"));

    imageLabel = new QLabel;
    imageLabel->setWordWrap(true);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setPixmap(QPixmap(":/images/image.png"));

    trackList = new QListWidget;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(imageLabel, 0, 0, 3, 2);
    layout->addWidget(profileLabel, 0, 0);
    layout->addWidget(iconLabel, 0, 1);
    layout->addWidget(titleLabel, 1, 0, 1, 2);
    layout->addWidget(trackList, 2, 0, 1, 2);
    layout->setRowStretch(2, 1);
    box->setLayout(layout);

    return box;
}

void PlaylistManager::createMenuBar()
{
    QAction *addAction = new QAction(tr("&Add album..."), this);
    QAction *deleteAction = new QAction(tr("&Delete album..."), this);
    QAction *quitAction = new QAction(tr("&Quit"), this);
    QAction *aboutAction = new QAction(tr("&About"), this);
    QAction *aboutQtAction = new QAction(tr("About &Qt"), this);

    addAction->setShortcut(tr("Ctrl+A"));
    deleteAction->setShortcut(tr("Ctrl+D"));
    quitAction->setShortcuts(QKeySequence::Quit);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addAction);
    fileMenu->addAction(deleteAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    connect(addAction, &QAction::triggered,
            this, &PlaylistManager::addAlbum);
    connect(deleteAction, &QAction::triggered,
            this, &PlaylistManager::deleteAlbum);
    connect(quitAction, &QAction::triggered,
            this, &PlaylistManager::close);
    connect(aboutAction, &QAction::triggered,
            this, &PlaylistManager::about);
    connect(aboutQtAction, &QAction::triggered,
            qApp, &QApplication::aboutQt);
}

void PlaylistManager::showImageLabel()
{
    profileLabel->hide();
    titleLabel->hide();
    iconLabel->hide();
    trackList->hide();

    imageLabel->show();
}

QModelIndex PlaylistManager::indexOfArtist(const QString &artist)
{
    QSqlTableModel *artistModel = model->relationModel(2);

    for (int i = 0; i < artistModel->rowCount(); i++) {
        QSqlRecord record =  artistModel->record(i);
        if (record.value("artist") == artist)
            return artistModel->index(i, 1);
    }
    return QModelIndex();
}

void PlaylistManager::updateHeader(QModelIndex, int, int)
{
    adjustHeader();
}

void PlaylistManager::adjustHeader()
{
    albumView->hideColumn(0);
    albumView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    albumView->resizeColumnToContents(2);
    albumView->resizeColumnToContents(3);
}

void PlaylistManager::about()
{
    QMessageBox::about(this, tr("About Music Archive"),
            tr("<p>The <b>Music Archive</b> example shows how to present "
               "data from different data sources in the same application. "
               "The album titles, and the corresponding artists and release dates, "
               "are kept in a database, while each album's tracks are stored "
               "in an XML file. </p><p>The example also shows how to add as "
               "well as remove data from both the database and the "
               "associated XML file using the API provided by the Qt SQL and "
               "Qt XML modules, respectively.</p>"));
}
