#ifndef AUDIOINPUTMANAGER_H
#define AUDIOINPUTMANAGER_H

#include <QWidget>
#include <QAudioDeviceInfo>
#include <QAudioRecorder>


namespace Ui {
class AudioInputManager;
}

class AudioInputManager : public QWidget
{
    Q_OBJECT

public:
    explicit AudioInputManager(QWidget *parent = nullptr);
    ~AudioInputManager();

    QAudioDeviceInfo deviceInfo;
    QAudioFormat settings;
    QAudio::Mode mode;

//public slots:
//    void record();
//    void stop();

signals:
    void recordingChanged();

private slots:
    QList<QAudioDeviceInfo> listDevices();

private:
    Ui::AudioInputManager *ui;
    QAudioRecorder *audioRecoder;
    bool isRecording;



};

#endif // AUDIOINPUTMANAGER_H
