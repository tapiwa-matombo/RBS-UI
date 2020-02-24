#include "broadcastmanager.h"
#include "ui_broadcastmanager.h"

BroadcastManager::BroadcastManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BroadcastManager)
{
    ui->setupUi(this);
}

BroadcastManager::~BroadcastManager()
{
    delete ui;
}
