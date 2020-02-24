#include "tracksmanager.h"
#include "ui_tracksmanager.h"

TracksManager::TracksManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TracksManager)
{
    ui->setupUi(this);
    setWindowTitle(tr("Tracks Manager"));
}

TracksManager::~TracksManager()
{
    delete ui;
}
