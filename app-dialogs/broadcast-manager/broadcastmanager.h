#ifndef BROADCASTMANAGER_H
#define BROADCASTMANAGER_H

#include <QWidget>

namespace Ui {
class BroadcastManager;
}

class BroadcastManager : public QWidget
{
    Q_OBJECT

public:
    explicit BroadcastManager(QWidget *parent = nullptr);
    ~BroadcastManager();

private:
    Ui::BroadcastManager *ui;
};

#endif // BROADCASTMANAGER_H
