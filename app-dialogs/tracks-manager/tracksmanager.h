#ifndef TRACKSMANAGER_H
#define TRACKSMANAGER_H

#include <QWidget>

namespace Ui {
class TracksManager;
}

class TracksManager : public QWidget
{
    Q_OBJECT

public:
    explicit TracksManager(QWidget *parent = nullptr);
    ~TracksManager();

private:
    Ui::TracksManager *ui;
};

#endif // TRACKSMANAGER_H
