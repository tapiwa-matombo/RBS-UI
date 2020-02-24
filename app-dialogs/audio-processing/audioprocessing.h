#ifndef AUDIOPROCESSING_H
#define AUDIOPROCESSING_H

#include <QWidget>

namespace Ui {
class AudioProcessing;
}

class AudioProcessing : public QWidget
{
    Q_OBJECT

public:
    explicit AudioProcessing(QWidget *parent = nullptr);
    ~AudioProcessing();

private:
    Ui::AudioProcessing *ui;
};

#endif // AUDIOPROCESSING_H
