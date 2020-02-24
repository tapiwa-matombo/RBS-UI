#include "programscheduler.h"
#include "ui_programscheduler.h"

ProgramScheduler::ProgramScheduler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramScheduler)
{
    ui->setupUi(this);
}

ProgramScheduler::~ProgramScheduler()
{
    delete ui;
}
