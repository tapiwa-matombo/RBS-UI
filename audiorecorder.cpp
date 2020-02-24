#include "audiorecorder.h"

#include <QAudioRecorder>
#include <QUrl>

AudioRecorder :: AudioRecorder ( QObject * parent ) : QObject ( parent ) {
    q_audioRecorder = new QAudioRecorder ( this );

    q_audioRecorder -> setOutputLocation ( QUrl ( "C:/Users/aleandra tinoe/Music/audio.wav" ));

    b_recording = false;
}

const bool &AudioRecorder::recording() {
    return b_recording;
}

void AudioRecorder::record()
{
    if ( q_audioRecorder -> state ( ) == QMediaRecorder :: StoppedState ) {
        q_audioRecorder -> record ( );

        b_recording = true;
        emit recordingChanged ( );
    }
}

void AudioRecorder::stop(){
    if ( q_audioRecorder -> state ( ) == QMediaRecorder::RecordingState ) {
        q_audioRecorder -> stop ( );

        b_recording = false;
        emit recordingChanged ( );
    }
}
