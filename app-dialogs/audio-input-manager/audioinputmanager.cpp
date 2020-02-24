#include "audioinputmanager.h"
#include "ui_audioinputmanager.h"

#include <QAudioRecorder>
#include <QUrl>

AudioInputManager::AudioInputManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioInputManager)
{
    ui->setupUi(this);

    mode = QAudio::AudioOutput;

}

AudioInputManager::~AudioInputManager()
{
    delete ui;
}

QList<QAudioDeviceInfo> AudioInputManager::listDevices()
{
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    return devices;

}



