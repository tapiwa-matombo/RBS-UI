#include "rbs.h"
#include "ui_rbs.h"
#include "db/dba.h"
#include "ui-components/library/library.h"
#include "players/player.h"
#include "ui-components/Buttons/volumebutton.h"

#include <QFileSystemModel>
#include <QAudioInput>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtWidgets>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

rbs::rbs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::rbs)
{
     ui->setupUi(this);
     setBroadcastWidget();
     setQueueWidget();

     getAudioInputsConnected();
     getAudioOutputsConnected();

     setMicrophoneInputVisualCues();
     qDebug() << "Running rbs ui";
     qDebug() << dba->initDb();
}

rbs::~rbs()
{
    delete ui;
}
//#########Start Music Library #########################################
void rbs::setLibraryWidget()
{
    //List music sources
    Library *fileView = new Library;
    fileView->displayLibraryTree(ui->libraryTreeView);
    ui->libraryTreeView->setAcceptDrops(true);

    // On selection of folder load children with file info on the list panel

}

//############### Start Music Library ##################################
void rbs::on_btnAddLibrary_clicked()
{
    Library *library = new Library;
    //call the input box here
    bool ok;
    QString libraryName = QInputDialog::getText(this, tr("Library name")
                          , tr("Library name: ")
                          , QLineEdit::Normal
                          , QDir::home().dirName(),&ok);
    if (ok && !libraryName.isEmpty())
    {
      //get a library name call add library
      qDebug() << libraryName;
      library->addLibrary(ui->libraryTableView,libraryName);
    }
}

void rbs::setDeckWidget()
{
    // TODO: Activate UI Widgtes for Deck widgets
    ui->deckAFrame->setAcceptDrops(true);
}
void rbs::setInstantPlayerWidget()
{
    // TODO: Activate UI |WIdgets for instant player
    ui->instantPlayersFrame->setAcceptDrops(true);
}
void rbs::setAuxillaryPlayerWidget()
{
    // TODO: Activate Auxillary players
    ui->auxillaryPlayerFrame->setAcceptDrops(true);
}

bool rbs::getAudioInputsConnected()
{
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QList<QString> inputdevicelist;
    if(devices.count() > 0){
        foreach (QAudioDeviceInfo i, devices) {
            //Add devices to a global list of devices
            inputDevices.append(i);
            qDebug() << i.deviceName();
        }
        // set text for status label
        QLabel *statusLabel = new QLabel(this);
        int d =  devices.count();
        QString printable = QStringLiteral("Mics: %1").arg(d);
        statusLabel->setText(printable);
        ui->statusBar->addPermanentWidget(statusLabel);
        return true;
    }
    return false;
}

//### set database
void rbs::setDatabase()
{
    //check database or create

}

//#### Open Sidebar Menu windows on click
//TODO: Every sidebar widget to open and activate window
void rbs::on_btnAudioProcessing_clicked()
{
    audioprocessing->show();
}

void rbs::on_btnPlaylistBuilder_clicked()
{
    playlistbuilder->show();
}

//############################## Start Broadcast Player Functionality #############################
void rbs::setBroadcastWidget()
{
    // TODO: Set the broadcast widget as the always on top widget and main controller
    // Player controls
    ui->broadcastFrame->setAcceptDrops(true);

    ui->btnVolume->setToolTip(tr("Adjust volume"));
    ui->volumeSlider->setHidden(true);


    ui->btnPlay->setToolTip(tr("Play track"));
    ui->btnShuffle->setToolTip("Shuffle playlist");
    ui->btnRecord->setToolTip(tr("Rocord current broadcast"));
    ui->btnRepeat->setToolTip(tr("Repeat current broadcast track"));
    ui->btnToStart->setToolTip(tr("Play track from start"));

    //## Mic
    ui->btnMic1->setToolTip(tr("Microphone 1"));
    ui->micPogressBar->setToolTip(tr("Mic level"));
    ui->micPogressBar->setValue(0);

    ui->btnMic1_2->setToolTip(tr("Microphone 2"));
    ui->micPogressBar_2->setToolTip(tr("Mic level"));
    ui->micPogressBar_2->setValue(0);

    ui->btnMic1_3->setToolTip(tr("Microphone 3"));
    ui->micPogressBar_3->setToolTip(tr("Mic level"));
    ui->micPogressBar_3->setValue(0);

    ui->btnBroadcast->setToolTip(tr("Toggle broadcast state"));
    ui->btnBroadcast->setIcon(QIcon(":/ui/icons/broadcastw.png"));

    ui->lblOnAir->setToolTip(tr("On/Off air status"));
    ui->lblOnAir->setText(tr("Off Air"));

    //## Track Info
    ui->lblTitle->setToolTip(tr("Current Track details"));
    ui->lblTitle->setText(tr("Track title"));

    ui->lblCountDown->setToolTip(tr("Track duration"));
    ui->lblCountDown->setText(tr("00:00"));

    ui->lblCountDownNg->setToolTip(tr("Track count down"));
    ui->lblCountDownNg->setText(tr("00:00"));

    ui->playProgressBar->setToolTip(tr("Track progress"));
    ui->playProgressBar->setValue(0);
    ui->playProgressBar->setRange(0,100);

    //Buttons visual state
    ui->btnRecord->setIcon(QIcon(":/ui/icons/recordw.png"));

    //## Player slots and signals setup
    //connect(broadcastPlayer, &QMediaPlayer::stateChanged, this, &rbs::stateChanged);
    connect(broadcastPlayer, &QMediaPlayer::positionChanged, this, &rbs::positionChanged);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
}

void rbs::positionChanged(qint64 position)
{
    if(ui->playProgressBar->maximum() != broadcastPlayer->duration())
    {
       ui->playProgressBar->setMaximum(broadcastPlayer->duration());
    }
    ui->playProgressBar->setValue(position);
    int seconds = (position/1000) % 60;
    int minutes = (position/60000) % 60;
    int hours = (position/3600000) % 24;
    QTime time(hours, minutes, seconds);
    ui->lblCountDown->setText(time.toString());
    qDebug() << broadcastPlayer->duration();
}

void rbs::setBroadcastPlayerMedia()
{
    QMediaPlaylist *bplaylist = new QMediaPlaylist(broadcastPlayer);
    broadcastPlayer->setPlaylist(bplaylist);

    QString directory = QFileDialog::getExistingDirectory(this,tr("Select dir for files to import"));
    if(directory.isEmpty())
        return;
    QDir dir(directory);
    QStringList files = dir.entryList(QStringList() << "*.mp3",QDir::Files);
    QList<QMediaContent> content;
    for(const QString& f:files)
    {
        content.push_back(QUrl::fromLocalFile(dir.path()+"/" + f));
        QFileInfo fi(f);
        ui->listWidgetQ->addItem(fi.fileName());
    }
    bplaylist->addMedia(content);
    ui->listWidgetQ->setCurrentRow(bplaylist->currentIndex() != -1? bplaylist->currentIndex():0);
}

void rbs::getMetaData()
{
    QVariant v;
    QString title;
    if(broadcastPlayer->isMetaDataAvailable())
    {
        v = broadcastPlayer->metaData("Title");
        title = v.value<QString>();
        ui->lblTitle->setText(title);
    }

    title =  broadcastPlayer->playlist()->currentMedia().canonicalUrl().fileName();
    ui->lblTitle->setText(title);
}

void rbs::on_btnShuffle_clicked()
{
    broadcastPlayer->playlist()->shuffle();
    getMetaData();
}

void rbs::on_btnRepeat_clicked()
{
    broadcastPlayer->playlist()->playbackMode();
    getMetaData();
}

void rbs::on_btnPlay_clicked()
{
    if (broadcastPlayer->mediaStatus() == QMediaPlayer::NoMedia)
    {
        setBroadcastPlayerMedia();
        broadcastPlayer->play();
        ui->btnPlay->setIcon(QIcon(":/ui/icons/stopb.png"));
        getMetaData();
    }
    else if (broadcastPlayer->state() == QMediaPlayer::PlayingState)
    {
        broadcastPlayer->stop();
        ui->btnPlay->setIcon(QIcon(":/ui/icons/play-buttonb.png"));
    }
    else
    {
        broadcastPlayer->play();
        ui->btnPlay->setIcon(QIcon(":/ui/icons/stopb.png"));

    }
}

void rbs::on_btnVolume_clicked()
{
   if(ui->volumeSlider->isHidden())
   {
       ui->volumeSlider->show();
       ui->btnVolume->setIcon(QIcon(":/ui/icons/volumeb.png"));
   } else {
       ui->volumeSlider->hide();
       ui->btnVolume->setIcon(QIcon(":/ui/icons/volumew.png"));
   }
}

void rbs::on_btnToStart_clicked()
{
    broadcastPlayer->setPosition(0);
    broadcastPlayer->play();
}

void rbs::on_volumeSlider_valueChanged(int value)
{
    connect(ui->volumeSlider, SIGNAL(valueChanged(qint64)),this,SLOT(broadcastPlayer->setVolume()));
    broadcastPlayer->setVolume(value);
}

void rbs::on_volumeSlider_sliderReleased()
{
    ui->volumeSlider->hide();
}

bool rbs::savePlaylist()
{
    QUrl location = QUrl("/playlists");
    return false;
}

//############################## End Broadcast Functionality ##############################

//#### Start Deck B Functionality ####
void rbs::on_btnPlayDeckA_2_clicked()
{
    deckBPlayer->togglePlayback();
}

//### End deck B Functionality ####

//############################# Start Deck A functionality ################################
void rbs::on_btnPlayDeckA_clicked()
{

}

void rbs::setQueueWidget()
{
    //TODO: Activate UI widgets for Queue widgets
    ui->queueControlsWidget->setAcceptDrops(true);
    ui->btnPlayDeckA->setIcon(QIcon(":/ui/icons/play-buttonb.png"));
    ui->btnVolumeDeckA->setIcon(QIcon(":/ui/icons/volumew.png"));
    ui->btnListenInDeckA->setIcon(QIcon(":/ui/icons/headphonesw.png"));
    ui->btnVisualizerOptionsDeckA->setIcon(QIcon(":/ui/icons/musical-notew.png"));
    ui->btnEqualizerDeckA->setIcon(QIcon(":/ui/icons/equalizerw.png"));
}
//############################ End Deck A Functionality #####################################


void rbs::on_btnVolumeDeckA_clicked()
{
    // Allow volume adjustment
    // Add Volume button class for a specific player
}

void rbs::on_btnPlayInst1_clicked()
{
    instantPlayer->togglePlayback();
}

void rbs::on_btnTracksManager_clicked()
{
    tracksmanager->show();
}

void rbs::on_btnAudioInputManager_clicked()
{
    audioinputmanager->show();
}

void rbs::on_btnSchedules_clicked()
{
    programscheduler->show();
}

void rbs::on_btnBroadcastManager_clicked()
{
    broadcastmanager->show();
}

//####### setting up microphines and input recording ###############
//To pass device source
void rbs::setupFormat()
{
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    qDebug() << info.deviceName();
    if (!info.isFormatSupported(format))
    {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }
}

void rbs::startRecording()
{
    // setup recording process here
    QFile destinationFile;
    destinationFile.setFileName("/recordings/test.raw");
    destinationFile.open(QIODevice::WriteOnly| QIODevice::Truncate);

    //Set up desired format
    setupFormat();

    QTimer::singleShot(3000, this, SLOT(stopRecording(audio)));
    audio->start(&destinationFile);
    // Records audio for 3000ms
}

void rbs::stopRecording(QAudioInput* audio)
{
    audio->stop();
    delete audio;
}

void rbs::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
            case QAudio::StoppedState:
                if (audio->error() != QAudio::NoError) {
                    // Error handling
                    qDebug() << audio->error();
                    ui->btnRecord->setIcon(QIcon(":/ui/icons/recordw.png"));
                } else {
                    // Finished recording
                    ui->btnRecord->setIcon(QIcon(":/ui/icons/recordw.png"));
                }
                break;

            case QAudio::ActiveState:
                // Started recording - read from IO device
                ui->btnRecord->setIcon(QIcon(":/ui/icons/recordb.png"));
                break;

            default:
                // ... other cases as appropriate
                break;
    }
}

void rbs::setMicrophoneInputVisualCues()
{
    qDebug() << inputDevices.count();
    if(inputDevices.count() > 0)
    {
        foreach (QAudioDeviceInfo mics, inputDevices)
        {
            ui->btnMic1->setIcon(QIcon(":/ui/icons/microphoneb.png"));
            ui->btnMic1->setToolTip(mics.deviceName());
        }
    }
    else
    {
        ui->btnMic1->setIcon(QIcon(":/ui/icons/microphonew.png"));
        ui->btnMic1->setDisabled(true);
        ui->btnMic1->setToolTip(tr("Microphone not connected."));


        ui->btnMic1_2->setIcon(QIcon(":/ui/icons/microphonew.png"));
        ui->btnMic1_2->setDisabled(true);
        ui->btnMic1_2->setToolTip(tr("Microphone not connected."));


        ui->btnMic1_3->setIcon(QIcon(":/ui/icons/microphonew.png"));
        ui->btnMic1_3->setDisabled(true);
        ui->btnMic1_3->setToolTip(tr("Microphone not connected."));
    }

}

void rbs::showActiveAudioLevels()
{

}

void rbs::on_btnRecord_clicked()
{
    startRecording();
}

void rbs::on_btnMic1_clicked()
{
    // Open mic input
}

void rbs::setMicInputs(QAudioInput *mic)
{

}

bool rbs::getAudioOutputsConnected()
{
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    QList<QString> outputdevicelist;
    if(devices.count() > 0){
        foreach (QAudioDeviceInfo i, devices) {
            //Add devices to a global list of devices
            outputDevices.append(i);
            qDebug() << i.deviceName();
        }
        // set text for status label
        QLabel *statusLabel2 = new QLabel(this);
        int d =  devices.count();
        QString printable = QStringLiteral("Mics: %1 |").arg(d);
        statusLabel2->setText(printable);
        ui->statusBar->addPermanentWidget(statusLabel2);
        return true;
    }
    return false;
}

//####### END setting up microphines and input recording ###############

void rbs::on_btnUsersManager_clicked()
{

}
