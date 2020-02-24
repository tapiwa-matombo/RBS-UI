#ifndef PROGRAMSCHEDULER_H
#define PROGRAMSCHEDULER_H

#include <QWidget>

namespace Ui {
class ProgramScheduler;
}

class ProgramScheduler : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramScheduler(QWidget *parent = nullptr);
    ~ProgramScheduler();

private:
    Ui::ProgramScheduler *ui;
};

#endif // PROGRAMSCHEDULER_H
