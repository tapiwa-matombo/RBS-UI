#include "playlistbuilder.h"
#include "ui_playlistbuilder.h"

#include <QGridLayout>
#include <QStandardPaths>
#include <QtWidgets>
#include <QSplitter>

PlaylistBuilder::PlaylistBuilder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistBuilder)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Playlist Builder"));
    // there should only be one instance of a player in this module


}

PlaylistBuilder::~PlaylistBuilder()
{
    delete ui;
}


void PlaylistBuilder::addItemsToTable(QFileInfo fi)
{
    auto row = ui->tblSongsTable->rowCount();
    ui->tblSongsTable->insertRow(row);
    auto item = new QTableWidgetItem(fi.fileName());
    auto pathString = new QTableWidgetItem(fi.filePath());
    qDebug() << fi.filePath();
    ui->tblSongsTable->setItem(row, 2, item);
    ui->tblSongsTable->setItem(row, 3, pathString);
}

void PlaylistBuilder::addDirectory()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select dir for files to import")
                    ,QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()),
                                                          QFileDialog::ShowDirsOnly|QFileDialog::DontUseNativeDialog);
    if(directory.isEmpty())
        return;
    QDir dir(directory);
    QStringList files = dir.entryList(QStringList() << "*.mp3",QDir::Files);
    QList<QMediaContent> content;
    for(const QString& f:files)
    {
        content.push_back(QUrl::fromLocalFile(dir.path()+"/" + f));
        QFileInfo fi(f);
        addItemsToTable(fi);
    }
    qDebug() << "Adding directory function";
    qDebug() << "playlist creation line";
    playlist->addMedia(content);
    playlist->setCurrentIndex(0);

    player->setPlaylist(playlist);
    player->play();

    ui->btnPlaySample->setText("Stop");
    qDebug() << "playlist validity test line";
    qDebug() << playlist->isEmpty();
    qDebug() << "playlist media count line";
    qDebug() << playlist->mediaCount();
    //ui->tblSongsTable->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
}

void PlaylistBuilder::getMetaFileMetadata(QList<QUrl> files)
{
    //Access each file on disk and do the following
    //Get file name
    //Get file path
    //Get file metadata
    //Add file to a db awaiting list
    //When user saves playlist else exits
    //Prompt to save
    //Write to database and save playlist
}

void PlaylistBuilder::setTableWidgetDnD()
{

}

void PlaylistBuilder::addFile()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open File"));
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        playUrl(fileDialog.selectedUrls().constFirst());
}

void PlaylistBuilder::playUrl(const QUrl &url)
{
    QString fileName;
    ui->btnPlaySample->setEnabled(true);
    if (url.isLocalFile()) {
        const QString filePath = url.toLocalFile();
        fileName = QFileInfo(filePath).fileName();

        ui->lblInfo->setText(fileName);
        ui->btnPlaySample->setText("Stop");
    } else {
        ui->lblInfo->setText(url.toString());
        fileName.clear();
    }
    player->setMedia(url);
    player->play();
}

void PlaylistBuilder::savePlaylist()
{
   if(!playlist->isEmpty())
   {
       QString filename = QFileDialog::getSaveFileName(this, "Save Playlist", QDir::currentPath(),"Text files(.txt);;All files(.)");
       playlist->save(QUrl::fromLocalFile(filename),"m3u");
       qDebug() << "Playlist saved successfully";
   }
   else
   {
       qDebug() << playlist->error();
   }
}

void PlaylistBuilder::on_btnSavePlaylist_clicked()
{
    // Save a created playlist
    savePlaylist();
}

void PlaylistBuilder::on_btnPlaySample_clicked()
{
    if (ui->btnPlaySample->text() == "Stop")
    {
        player->stop();
        ui->btnPlaySample->setText(tr("Play"));
        ui->lblInfo->setText("No media playing");
    }
    else if(ui->btnPlaySample->text() == "Play")
    {
        if (player->mediaStatus() == QMediaPlayer::NoMedia)
        {
            //prompt user to add music
            QMessageBox msgBox;
            msgBox.setText("No Media");
            msgBox.setInformativeText("'Add File' or 'Import Folder' to Play!");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
    }
}

void PlaylistBuilder::onFileSelected()
{

}

void PlaylistBuilder::onDirectorySelected()
{

}

void PlaylistBuilder::createPlaylist()
{
    //add folder if no items are in table
    //add file if no song item is added to table
}

void PlaylistBuilder::on_btnAddFolder_clicked()
{
    addDirectory();
}

void PlaylistBuilder::on_btnRepeat_clicked()
{
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
}

void PlaylistBuilder::on_tblSongsTable_itemClicked(QTableWidgetItem *item)
{
    qDebug() << item->row();
}

bool PlaylistBuilder::loadPlaylist(QUrl location)
{
    return true;
}

void PlaylistBuilder::on_btnNext_clicked()
{
    playlist->next();
}

void PlaylistBuilder::data()
{

}

void PlaylistBuilder::on_btnPrevious_clicked()
{
    playlist->previous();
}

void PlaylistBuilder::on_btnAddFile_clicked()
{
    addFile();
}

void PlaylistBuilder::on_tblSongsTable_itemDoubleClicked(QTableWidgetItem *item)
{
    int selectedSong = item->row();
    playlist->setCurrentIndex(selectedSong);
    qDebug() << item->data(0).convert(QVariant::String);
    QString songTitle;
}
