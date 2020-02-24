#include "usersmanager.h"
#include "ui_usersmanager.h"

UsersManager::UsersManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsersManager)
{
    ui->setupUi(this);
}

UsersManager::~UsersManager()
{
    delete ui;
}
