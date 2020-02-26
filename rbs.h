#ifndef RBS_H
#define RBS_H

#include "ui-components/library/library.h"
#include "players/player.h"
#include "db/dba.h"
#include "app-dialogs/audio-input-manager/audioinputmanager.h"
#include "app-dialogs/broadcast-manager/broadcastmanager.h"
#include "app-dialogs/audio-processing/audioprocessing.h"
#include "app-dialogs/playlist-builder/playlistbuilder.h"
#include "app-dialogs/tracks-manager/tracksmanager.h"
#include "app-dialogs/program-scheduler/programscheduler.h"
#include "app-dialogs/users-manager/usersmanager.h"
#include "app-dialogs/settings-manager/settingsmanager.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QMainWindow>


QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)


namespace Ui {
class rbs;
}

class Library;
class Player;

class rbs : public QMainWindow
{
    Q_OBJECT

public:
    explicit rbs(QWidget *parent = nullptr);
    ~rbs() override;
    void getMetaData();

    
    void setupFormat();

protected:
    //bool event(QEvent *event) override;
    //void dropEvent(QDropEvent *event) override

public slots:
    void positionChanged(qint64 position);

    //Widget setup
    void setLibraryWidget();
    void setQueueWidget();
    void setDeckWidget();
    void setInstantPlayerWidget();
    void setAuxillaryPlayerWidget();
    void setBroadcastWidget();
    void setBroadcastPlayerMedia();
    void setDatabase();

    // Recording devices and audio input detection
    bool getAudioInputsConnected();
    void stopRecording(QAudioInput* audio);
    void startRecording();
    void handleStateChanged(QAudio::State state);
    void setMicrophoneInputVisualCues();
    void showActiveAudioLevels();
    void setMicInputs(QAudioInput *mic);

    // AudioOutput Devices and audio output detection
    bool getAudioOutputsConnected();

    bool savePlaylist();

private slots:
    void on_btnAddLibrary_clicked();

    void on_btnAudioProcessing_clicked();

    void on_btnPlay_clicked();

    void on_btnPlayDeckA_2_clicked();

    void on_btnPlayDeckA_clicked();

    void on_btnPlayInst1_clicked();

    void on_btnPlaylistBuilder_clicked();

    void on_btnVolumeDeckA_clicked();

    void on_btnVolume_clicked();

    void on_btnToStart_clicked();

    void on_volumeSlider_valueChanged(int value);

    void on_volumeSlider_sliderReleased();

    void on_btnTracksManager_clicked();

    void on_btnSchedules_clicked();

    void on_btnAudioInputManager_clicked();

    void on_btnBroadcastManager_clicked();

//    void on_playProgressBar_valueChanged(int value);

    void on_btnRepeat_clicked();

    void on_btnShuffle_clicked();

    void on_btnRecord_clicked();

    void on_btnMic1_clicked();

    void on_btnUsersManager_clicked();

    void on_tableWidgetQ_itemClicked(QTableWidgetItem *item);

private:
    Ui::rbs *ui;
    AudioInputManager *audioinputmanager = new AudioInputManager();
    BroadcastManager *broadcastmanager = new BroadcastManager();
    AudioProcessing *audioprocessing = new AudioProcessing;
    PlaylistBuilder *playlistbuilder = new PlaylistBuilder();
    TracksManager *tracksmanager = new TracksManager();
    ProgramScheduler *programscheduler = new ProgramScheduler();
    UsersManager *usersmanager = new UsersManager();
    SettingsManager *settingsmanager = new SettingsManager();

    QMediaPlayer *broadcastPlayer = new QMediaPlayer();
    QMediaPlayer  *deckAPlayer = new QMediaPlayer();

    Player *deckBPlayer = new Player();
    Player *instantPlayer = new Player();
    Player *auxillaryPlayer = new Player();
    Player *queuePlayer = new Player();

    DBA *dba = new DBA(this);

    QMenu *menu = nullptr;
    QLabel *label = nullptr;
    QSlider *slider = nullptr;

    QAudioFormat format;
    QList<QAudioDeviceInfo> inputDevices;
    QList<QAudioDeviceInfo> outputDevices;
    QAudioInput *audio = new QAudioInput(format, this);
};

#endif // RBS_H
