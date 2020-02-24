#include "audioprocessing.h"
#include "ui_audioprocessing.h"

AudioProcessing::AudioProcessing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioProcessing)
{
    ui->setupUi(this);
    setWindowTitle(tr("Audio Processing"));
}

AudioProcessing::~AudioProcessing()
{
    delete ui;
}
