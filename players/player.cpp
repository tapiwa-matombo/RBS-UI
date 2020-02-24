#include "player.h"
#include "ui-components/Buttons/volumebutton.h"
//TODO: Code a basic player with drag and drop functionality

#include <QtWidgets>
#include <QDebug>

Player::Player(QWidget *parent) : QWidget(parent)
{
    connect(&mediaPlayer, &QMediaPlayer::positionChanged, this, &Player::updatePosition);
    connect(&mediaPlayer, &QMediaPlayer::durationChanged, this, &Player::updateDuration);
    connect(&mediaPlayer, &QMediaObject::metaDataAvailableChanged, this, &Player::updateInfo);

    connect(&mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            this, &Player::handleError);

    connect(&mediaPlayer, &QMediaPlayer::stateChanged,
            this, &Player::updateState);

    connect(&mediaPlayer, &QMediaPlayer::volumeChanged, this, &Player::setVolume);

    setAcceptDrops(true);
}

QStringList Player::supportedMimeTypes()
{
    QStringList result = QMediaPlayer::supportedMimeTypes();
    if (result.isEmpty())
        result.append(QStringLiteral("audio/mpeg"));
    return result;
}

void Player::openFile()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open File"));
    fileDialog.setMimeTypeFilters(Player::supportedMimeTypes());
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        playUrl(fileDialog.selectedUrls().constFirst());
}

void Player::playUrl(const QUrl &url)
{
    //playButton->setEnabled(true);
    if (url.isLocalFile()) {
        const QString filePath = url.toLocalFile();
        setWindowFilePath(filePath);
        //infoLabel->setText(QDir::toNativeSeparators(filePath));
        fileName = QFileInfo(filePath).fileName();
    } else {
        setWindowFilePath(QString());
        //infoLabel->setText(url.toString());
        fileName.clear();
    }
    mediaPlayer.setMedia(url);
    mediaPlayer.play();
}

void Player::togglePlayback()
{
    if (mediaPlayer.mediaStatus() == QMediaPlayer::NoMedia)
        openFile();
    else if (mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();
}

void Player::seekForward()
{
    //positionSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void Player::seekBackward()
{
    //positionSlider->triggerAction(QSlider::SliderPageStepSub);
}

//! [0]
bool Player::event(QEvent *event)
{
    //if (event->type() == QWinEvent::CompositionChange || event->type() == QWinEvent::ColorizationChange)
     //   return true;
    return QWidget::event(event);
}
//! [0]

static bool canHandleDrop(const QDropEvent *event)
{
    const QList<QUrl> urls = event->mimeData()->urls();
    if (urls.size() != 1)
        return false;
    QMimeDatabase mimeDatabase;
    return Player::supportedMimeTypes().
        contains(mimeDatabase.mimeTypeForUrl(urls.constFirst()).name());
}

void Player::dragEnterEvent(QDragEnterEvent *event)
{
    event->setAccepted(canHandleDrop(event));
}

void Player::dropEvent(QDropEvent *event)
{
    event->accept();
    playUrl(event->mimeData()->urls().constFirst());
}

void Player::mousePressEvent(QMouseEvent *event)
{
    offset = event->globalPos() - pos();
    event->accept();
}

void Player::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - offset);
    event->accept();
}

void Player::mouseReleaseEvent(QMouseEvent *event)
{
    offset = QPoint();
    event->accept();
}

void Player::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState) {
       //playButton->setToolTip(tr("Pause"));
      // playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
       //playButton->setToolTip(tr("Play"));
       //playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

static QString formatTime(qint64 timeMilliSeconds)
{
    qint64 seconds = timeMilliSeconds / 1000;
    const qint64 minutes = seconds / 60;
    seconds -= minutes * 60;
    return QStringLiteral("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

void Player::updatePosition(qint64 /*position*/)
{
     //progressBar->setValue(position);
     //positionLabel->setText(formatTime(position));
}

void Player::updateDuration(qint64 /*duration*/)
{
    //Replace slider with progress bar
    //positionSlider->setRange(0, duration);
    //positionSlider->setEnabled(duration > 0);
    //positionSlider->setPageStep(duration / 10);
   // updateInfo();
}

void Player::setPosition(int position)
{
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(mediaPlayer.position() - position) > 99)
        mediaPlayer.setPosition(position);
}

void Player::updateInfo()
{
    QStringList info;
    if (!fileName.isEmpty())
        info.append(fileName);
    if (mediaPlayer.isMetaDataAvailable()) {
        QString author = mediaPlayer.metaData(QStringLiteral("Author")).toString();
        if (!author.isEmpty())
            info.append(author);
        QString title = mediaPlayer.metaData(QStringLiteral("Title")).toString();
        if (!title.isEmpty())
            info.append(title);
    }
    info.append(formatTime(mediaPlayer.duration()));
    //infoLabel->setText(info.join(tr(" - ")));
}

void Player::handleError()
{
    //playButton->setEnabled(false);
    const QString errorString = mediaPlayer.errorString();
    //infoLabel->setText(errorString.isEmpty()
                      // ? tr("Unknown error #%1").arg(int(mediaPlayer.error()))
                      // : tr("Error: %1").arg(errorString));
}

void Player::volumeControl()
{
    volumeButton = new VolumeButton(this);
    volumeButton->setToolTip(tr("Adjust volume"));
    volumeButton->setVolume(mediaPlayer.volume());
    connect(volumeButton, &VolumeButton::volumeChanged, &mediaPlayer, &QMediaPlayer::setVolume);
}

void Player::increaseVolume()
{

}

void Player::decreaseVolume()
{

}

int Player::volume(int value) const
{
    return value;
}

int Player::setVolume(int volume)
{
    return volume;
}
