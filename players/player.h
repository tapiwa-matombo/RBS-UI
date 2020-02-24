#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QtWinExtras/QWinEvent>
#include <QMediaPlayer>

class VolumeButton;

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);

    int volume(int value) const;

    static QStringList supportedMimeTypes();
    static QStringList supportedSuffixes();

signals:
    void volumeChanged(int volume);

public slots:
    void openFile();
    void playUrl(const QUrl& url);
    void togglePlayback();
    void seekForward();
    void seekBackward();
    void volumeControl();
    void increaseVolume();
    void decreaseVolume();
    int setVolume(int volume);

protected:
    bool event(QEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void updateInfo();
    void handleError();

private:

    QMediaPlayer mediaPlayer;
    VolumeButton *volumeButton = nullptr;
    QPoint offset;
    QString fileName;



};

#endif // PLAYER_H
